#include <sstream>
#include "CMEApplication.h"
#include "Logger.h"

#include "quickfix/fix42/Reject.h"
#include "quickfix/fix42/BusinessMessageReject.h"
#include "quickfix/fix42/NewOrderSingle.h"
#include "quickfix/fix42/TestRequest.h"
#include "quickfix/fix42/Heartbeat.h"
#include "quickfix/fix42/OrderCancelRequest.h"
#include "quickfix/fix42/OrderCancelReject.h"
#include "quickfix/fix42/ExecutionReport.h"
#include "quickfix/fix42/OrderStatusRequest.h"
#include "quickfix/fix42/OrderCancelReplaceRequest.h"
#include "quickfix/fix42/QuoteRequest.h"
#include "quickfix/fix42/SecurityDefinitionRequest.h"
#include "quickfix/fix42/QuoteCancel.h"
#include "quickfix/fix42/MassQuote.h"
#include "quickfix/fix44/OrderMassStatusRequest.h"
#include "quickfix/fix50sp2/OrderMassActionRequest.h"
#include "quickfix/fix50sp2/OrderMassActionReport.h"
#include "quickfix/fix44/NewOrderCross.h"

#include "cryptopp/cryptlib.h"
#include "cryptopp/hmac.h"
#include "cryptopp/sha.h"
#include "cryptopp/base64.h"
#include "cryptopp/filters.h"

namespace falcon {
    namespace cme {
        using  namespace FIX;

        CMEApplication::CMEApplication(std::string settingFile) :
                settings_(settingFile), storeFactory_(settings_), logFactory_(settings_),
                socketInitiator_(*this, storeFactory_, settings_, logFactory_){
            LOG("creating CME session...");
        }

        CMEApplication::~CMEApplication() {

            LOG("destruct CME session...");
        }
        bool CMEApplication::start() {
            this->socketInitiator_.start();
            return true;
        };

        bool CMEApplication::stop(bool force) {
            this->socketInitiator_.stop(force);
            return true;
        };

        SessionID CMEApplication::getSessionIDbyTargetCompID(const std::string targetCompID) {
            auto sessionSet = this->settings_.getSessions();

            SessionID res;
            for(auto rit = sessionSet.begin(); rit != sessionSet.end(); ++ rit ){
                if(rit->getTargetCompID() == targetCompID){
                    res = *rit;
                }
            }
            return res;
        };

        void CMEApplication::onCreate(const SessionID &sessionID) {
        };

        void CMEApplication::onLogon(const SessionID &sessionID) {
            std::cout << "Session " << sessionID.toString() << " Logged on..." << std::endl;
        };

        void CMEApplication::onLogout(const SessionID &sessionID) {
            std::cout << "Session " << sessionID.toString() << " Logged out..." << std::endl;
        };

        void CMEApplication::fromApp(const Message &message, const SessionID &sessionID)
            throw( FieldNotFound, IncorrectDataFormat, IncorrectTagValue, UnsupportedMessageType ) {
            auto msgSeqNum = message.getHeader().getField(FIX::FIELD::MsgSeqNum);
            std::lock_guard<std::mutex> guard(this->latestSeqNO_mutex);
            this->latestSeqNo = atol(msgSeqNum.c_str());

            std::stringstream sstream;
            sstream << "App msg latestSeqNo is " << this->latestSeqNo << std::endl;
            LOG(sstream.str());

            this->crack(message, sessionID);
        };

        void CMEApplication::fromAdmin(const Message &message, const SessionID &sessionID)
            throw( FieldNotFound, IncorrectDataFormat, IncorrectTagValue, RejectLogon ) {
            auto msgType = message.getHeader().getField(FIX::FIELD::MsgType);
            std::stringstream sstream;

            if(msgType == FIX::MsgType_Heartbeat) {
                sstream << "Heartbeat received from " << sessionID.toString() << std::endl;
            }
            else if(msgType == FIX::MsgType_ResendRequest){
                sstream << "Resend Request received from " << sessionID.toString() << std::endl;
            }
            else if(msgType == FIX::MsgType_SequenceReset){
                sstream << "Sequence Resset received from " << sessionID.toString() << std::endl;
            }
            else if(msgType == FIX::MsgType_Heartbeat) {
                sstream << "Heartbeat received from " << sessionID.toString() << std::endl;
            }
            else if(msgType == FIX::MsgType_TestRequest){
                sstream << "Test Request received from " << sessionID.toString() << std::endl;
            }
            else if(msgType == FIX::MsgType_Logon){
                sstream << "Logon ack received from " << sessionID.toString() << std::endl;
            }
            else if(msgType == FIX::MsgType_Logout){
                sstream << "Logout ack received from " << sessionID.toString() << std::endl;
            }
            else if(msgType == FIX::MsgType_Reject){
                sstream << "Session Level Reject received from " << sessionID.toString() << std::endl;
            }

            auto msgSeqNum = message.getHeader().getField(FIX::FIELD::MsgSeqNum);
            std::lock_guard<std::mutex> guard(this->latestSeqNO_mutex);
            this->latestSeqNo = atol(msgSeqNum.c_str());

            sstream << "latestSeqNo is " << this->latestSeqNo << std::endl;

            LOG(sstream.str());
        };

        void CMEApplication::toApp(Message &message, const SessionID &sessionID) throw( DoNotSend ) {
            this->setCMEHeader(message, sessionID);
        };

        void CMEApplication::toAdmin(Message &message, const SessionID &sessionID) {
            this->setCMEHeader(message, sessionID);

            auto msgType = message.getHeader().getField(FIX::FIELD::MsgType);

            if (msgType == FIX::MsgType_Logon) {
                this->setLogon(message, sessionID);
                std::cout << "Logon sent" << std::endl;
            }
            else if(msgType == FIX::MsgType_Logout){
                this->setLogout(message, sessionID);
                std::cout << "Logout sent" << std::endl;
            }
            else if(msgType == FIX::MsgType_Heartbeat){
                LOG("Heartbeat sent\n");
            }
            else if(msgType == FIX::MsgType_ResendRequest){
                auto beginSeqNoStr = message.getField(FIX::FIELD::BeginSeqNo);
                auto beginSeqNo = atol(beginSeqNoStr.c_str());
                //if(this->latestSeqNo - beginSeqNo >= 2500)
                //message.setField(FIX::EndSeqNo(beginSeqNo + 2499));

                std::stringstream sstream;
                sstream << "ResendRequest sent: beginSeqNo " << beginSeqNo << " latestSeqNo " << this->latestSeqNo << "\n";
                LOG(sstream.str());
            }
        }

        void CMEApplication::onMessage(const FIX42::BusinessMessageReject& businessMessageReject, const SessionID &sessionID) {
            if(this->observer_){
                this->observer_->onMessage(businessMessageReject);
            }
            LOG_ERR(businessMessageReject.toString());
        }

        void CMEApplication::onMessage(const FIX42::Reject& reject, const SessionID& sessionID) {
            if(this->observer_){
                this->observer_->onMessage(reject);
            }
            else{
                LOG_ERR(reject.toString());
            }
        }

        void CMEApplication::onMessage(const FIX42::OrderCancelReject& orderCancelReject, const SessionID& sessionID) {
            if(this->observer_){
                this->observer_->onMessage(orderCancelReject);
            }
            else{
                LOG(orderCancelReject.toString());
            }
        }

        void CMEApplication::onMessage(const FIX50SP2::OrderMassActionReport& orderMassActionReport){
            if(this->observer_){
                this->observer_->onMessage(orderMassActionReport);
            }
            else{
                LOG(orderMassActionReport.toString());
            }
        }

        void CMEApplication::onMessage(const FIX42::ExecutionReport &executionReport, const SessionID &sessionID) {
            auto execType = executionReport.getField(FIX::FIELD::ExecType);
            if(this->observer_){
                this->observer_->onMessage(executionReport);
            }
            else{
                LOG(executionReport.toString());
            }
        }

        void CMEApplication::onMessage(const FIX42::TestRequest &message, const SessionID &sessionID) {
            FIX::TestReqID testReqID;
            message.getField(testReqID);

            FIX42::Heartbeat heartbeat;
            heartbeat.setField(testReqID);
            Session::sendToTarget(heartbeat, sessionID);
        }

        void CMEApplication::setCMEHeader(Message &message, const SessionID &sessionID) {
            auto pSession = socketInitiator_.getSession(sessionID);

            if(!pSession)
                return;

            auto lastMsgSeqNumProcessed = pSession->getExpectedTargetNum()-1;
            auto targetSubID = settings_.get(sessionID).getString("TargetSubID");
            auto senderSubID = settings_.get(sessionID).getString("SenderSubID");
            auto senderLocationID = settings_.get(sessionID).getString("SenderLocationID");

            message.getHeader().setField(FIX::LastMsgSeqNumProcessed(lastMsgSeqNumProcessed));
            message.getHeader().setField(FIX::TargetSubID(targetSubID));
            message.getHeader().setField(FIX::SenderSubID(senderSubID));
            message.getHeader().setField(FIX::SenderLocationID(senderLocationID));
        }

        void CMEApplication::setLogon(Message &message, const SessionID &sessionID) {
            auto accessKeyID = settings_.get(sessionID).getString("AccessKeyID");
            auto secretKey = settings_.get(sessionID).getString("SecretKey");

            auto applicationSystemName = settings_.get(sessionID).getString("ApplicationSystemName");
            auto tradingSystemVersion = settings_.get(sessionID).getString("TradingSystemVersion");
            auto applicationSystemVendor = settings_.get(sessionID).getString("ApplicationSystemVendor");

            message.setField(FIX::EncodedTextLen(accessKeyID.length()));
            message.setField(FIX::EncodedText(accessKeyID));

            message.setField(1603, applicationSystemName);
            message.setField(1604, tradingSystemVersion);
            message.setField(1605, applicationSystemVendor);

            auto canonicalRequest = this->createCanonicalRequest(message, sessionID);
            auto encodedHMac = this->calculateHMAC(secretKey, canonicalRequest);

            message.setField(FIX::FIELD::EncryptedPasswordMethod, "CME-1-SHA-256");
            message.setField(FIX::EncryptedPasswordLen(encodedHMac.length()));
            message.setField(FIX::EncryptedPassword(encodedHMac));
        }

        void CMEApplication::setLogout(Message &message, const SessionID &sessionID) {
            FIX::MsgSeqNum msgSeqNum;
            message.getHeader().getField(msgSeqNum);

            message.setField(FIX::FIELD::NextExpectedMsgSeqNum, msgSeqNum.getString());//NextExpectedMsgSeqNum
        }

        std::string CMEApplication::createCanonicalRequest(const Message &logon, const SessionID &sessionID) {
            /*
            tag 34-MsgSeqNum – sequence number sent by client system
            tag 49-SenderCompID – sender comp ID including the Fault Tolerance Indicator (right-most character)
            tag 50-SenderSubID – Operator ID
            tag 52-SendingTime – timestamp in milliseconds, UTC time format. UTC Timestamps are sent in number of nanoseconds since Unix epoch synced to a master clock to microsecond accuracy.
            tag 57-TargetSubID – recipient of message.
                For iLink and Drop Copy sessions,
                    CGW session – ‘G’
                    MSGW session - two digit market segment ID
            tag 108-HeartBeatInterval – heartbeat interval specified in the logon message as number of seconds
            tag 142-SenderLocationID – assigned value used to identify specific message originator's location (i.e. geographic location)
            tag 369-LastMsgSeqNumProcessed – last message sequence number processed by the client system
            tag 1603-ApplicationSystemName – identifies system generating the message
            tag 1604-ApplicationSystemVersion – identifies the version of the system generating the message
            tag 1605-ApplicationSystemVendor – identifies the vendor of the application system
            */
            std::string canonicalRequest{""};

            auto msgSeqNum = logon.getHeader().getField(FIX::FIELD::MsgSeqNum);
            auto senderCompID = logon.getHeader().getField(FIX::FIELD::SenderCompID);
            auto sendderSubID = logon.getHeader().getField(FIX::FIELD::SenderSubID);
            auto sendingTime = logon.getHeader().getField(FIX::FIELD::SendingTime);
            auto targetSubID = logon.getHeader().getField(FIX::FIELD::TargetSubID);
            auto heartBeatInterval = logon.getHeader().getField(FIX::FIELD::HeartBtInt);
            auto senderLocationID = logon.getHeader().getField(FIX::FIELD::SenderLocationID);
            auto lastMsgSeqNumProcessed = logon.getHeader().getField(FIX::FIELD::LastMsgSeqNumProcessed);

            auto applicationSystemName = logon.getField(1603);
            auto applicationSystemVersion = logon.getField(1604);
            auto applicationSystemVendor = logon.getField(1605);

            canonicalRequest = msgSeqNum + "\n" +
                               senderCompID + "\n" +
                               sendderSubID + "\n" +
                               sendingTime + "\n" +
                               targetSubID + "\n" +
                               heartBeatInterval + "\n" +
                               senderLocationID + "\n" +
                               lastMsgSeqNumProcessed + "\n" +
                               applicationSystemName + "\n" +
                               applicationSystemVendor;

            return canonicalRequest;
        }

        std::string CMEApplication::calculateHMAC(const std::string &key, const std::string &canonicalRequest) {
            std::string decoded_key, calculatedHmac, encodedHmac;

            // Decode the key since it is base64url encoded
            CryptoPP::StringSource(key,
                                   true,
                                   new CryptoPP::Base64URLDecoder( new CryptoPP::StringSink(decoded_key)) // Base64URLDecoder
            ); // StringSource

            // Calculate HMAC
            CryptoPP::HMAC<CryptoPP::SHA256> hmac((CryptoPP::byte*)decoded_key.c_str(), decoded_key.size());

            CryptoPP::StringSource(canonicalRequest,
                                   true,
                                   new CryptoPP::HashFilter(hmac, new CryptoPP::StringSink(calculatedHmac)) // HashFilter
            ); // StringSource

            // base64url encode the HMAC and strip padding
            CryptoPP::StringSource(calculatedHmac,
                                   true,
                                   new CryptoPP::Base64URLEncoder(new CryptoPP::StringSink(encodedHmac)) // Base64URLEncoder
            ); // StringSource

            return encodedHmac;
        }

        bool CMEApplication::isSessionLoggedOn(const SessionID &sessionID) {
            return(this->socketInitiator_.getSession(sessionID)->isLoggedOn());
        }

        bool CMEApplication::setObserver(CMEOrderInterface *observer) {
            if(!this->observer_){
                this->observer_ = observer;
                return true;
            }
            else{
                return false;
            }
        }

        bool CMEApplication::sendTestRequest(const SessionID &sessionID, std::string testRequestID) {
            if(!this->isSessionLoggedOn(sessionID)){
                return false;
            }

            FIX42::TestRequest testRequest;
            testRequest.setField(FIX::TestReqID(testRequestID));
            Session::sendToTarget(testRequest, sessionID);

            return  true;
        }

        bool CMEApplication::sendOrderCancelRequest(const SessionID &sessionID,
                                                    std::string account,
                                                    std::string clOrdID,
                                                    std::string orderID,
                                                    std::string origClOrdID,
                                                    char side,
                                                    std::string securityDesc,
                                                    std::string securityType,
                                                    std::string correlationClOrdID,
                                                    bool manualOrderIndicator) {

            if(!this->isSessionLoggedOn(sessionID)){
                return false;
            }

            FIX42::OrderCancelRequest orderCancelRequest;
            orderCancelRequest.setField(FIX::Account(account));
            orderCancelRequest.setField(FIX::ClOrdID(clOrdID));
            orderCancelRequest.setField(FIX::OrderID(orderID));
            orderCancelRequest.setField(FIX::OrigClOrdID(origClOrdID));
            orderCancelRequest.setField(FIX::Side(side));
            orderCancelRequest.setField(FIX::TransactTime());
            orderCancelRequest.setField(FIX::ManualOrderIndicator(manualOrderIndicator));
            orderCancelRequest.setField(FIX::SecurityDesc(securityDesc));
            orderCancelRequest.setField(FIX::SecurityType(securityType));
            orderCancelRequest.setField(9717, correlationClOrdID); //CorrelationClOrdID

            Session::sendToTarget(orderCancelRequest, sessionID);

            return true;
        }

        bool CMEApplication::sendNewOrderSingle(const SessionID &sessionID,
                                                std::string account,
                                                std::string clOrdID,
                                                std::string custOrderHandlingInst,
                                                int32_t orderQty,
                                                char ordType,
                                                double price,
                                                char side,
                                                // std::string symbol,
                                                char timeInForce,
                                                double stopPx,
                                                std::string securityDesc,
                                                int32_t minQty,
                                                std::string securityType,
                                                int32_t customerOrFirm,
                                                int32_t maxShow,
                                                std::string expireDate,
                                                bool manualOrderIndicator,
                                                std::string giveUpFirm,
                                                std::string cmtaGiveupCD,
                                                std::string allocAccount) {
            if(!this->isSessionLoggedOn(sessionID)){
                return false;
            }

            FIX42::NewOrderSingle newOrderSingle;
            newOrderSingle.setField(FIX::Account(account));
            newOrderSingle.setField(FIX::ClOrdID(clOrdID));
            newOrderSingle.setField(FIX::HandlInst('1'));
            newOrderSingle.setField(FIX::CustOrderHandlingInst(custOrderHandlingInst));
            newOrderSingle.setField(FIX::OrderQty(orderQty));
            newOrderSingle.setField(FIX::OrdType(ordType));
            if(ordType == FIX::OrdType_LIMIT || ordType == FIX::OrdType_STOP_LIMIT)
                newOrderSingle.setField(FIX::Price(price));
            newOrderSingle.setField(FIX::Side(side));
            //Symbol
            newOrderSingle.setField(FIX::TimeInForce(timeInForce));
            newOrderSingle.setField(FIX::TransactTime());
            newOrderSingle.setField(FIX::ManualOrderIndicator(manualOrderIndicator));
            if(ordType == FIX::OrdType_STOP || ordType == FIX::OrdType_STOP_LIMIT)
                newOrderSingle.setField(FIX::StopPx(stopPx));
            newOrderSingle.setField(FIX::SecurityDesc(securityDesc));
            if(timeInForce == FIX::TimeInForce_IMMEDIATE_OR_CANCEL) //FAK
                newOrderSingle.setField(FIX::MinQty(minQty));
            newOrderSingle.setField(FIX::SecurityType(securityType));
            newOrderSingle.setField(FIX::CustomerOrFirm(customerOrFirm));
            if(timeInForce != FIX::TimeInForce_IMMEDIATE_OR_CANCEL) //FAK
                newOrderSingle.setField(FIX::MaxShow(maxShow));
            if(timeInForce == FIX::TimeInForce_GOOD_TILL_DATE)
                newOrderSingle.setField(FIX::ExpireDate(expireDate));
            newOrderSingle.setField(9702, "1");//CTiCode
            newOrderSingle.setField(9717, clOrdID);//CorrelationClOrdID

            if(cmtaGiveupCD == "GU" || cmtaGiveupCD == "SX"){//give up
                newOrderSingle.setField(FIX::NoAllocs(1));
                newOrderSingle.setField(FIX::AllocAccount(allocAccount));
                newOrderSingle.setField(9708, cmtaGiveupCD);
                newOrderSingle.setField(9707, giveUpFirm);
            }

            Session::sendToTarget(newOrderSingle, sessionID);

            return true;
        }

        bool CMEApplication::sendOrderCancelReplaceRequest(const SessionID &sessionID,
                                                           std::string account,
                                                           std::string clOrdID,
                                                           std::string orderID,
                                                           int32_t orderQty,
                                                           std::string custOrderHandlingInst,
                                                           char ordType,
                                                           std::string origClOrdID,
                                                           double price,
                                                           char side,
                                                           char timeInForce,
                                                           bool manualOrderIndicator,
                                                           double stopPx,
                                                           std::string securityDesc,
                                                           int32_t minQty,
                                                           std::string securityType,
                                                           int32_t customerOrFirm,
                                                           int32_t maxShow,
                                                           std::string expireDate,
                                                           std::string correlationClOrdID,
                                                           char IFMFlag,
                                                           std::string giveUpFirm,
                                                           std::string cmtaGiveupCD,
                                                           std::string allocAccount) {
            if(!this->isSessionLoggedOn(sessionID)){
                return false;
            }
            FIX42::OrderCancelReplaceRequest orderCancelReplaceRequest;
            orderCancelReplaceRequest.setField(FIX::Account(account));
            orderCancelReplaceRequest.setField(FIX::ClOrdID(clOrdID));
            orderCancelReplaceRequest.setField(FIX::OrderID(orderID));
            orderCancelReplaceRequest.setField(FIX::HandlInst('1'));
            orderCancelReplaceRequest.setField(FIX::OrderQty(orderQty));
            orderCancelReplaceRequest.setField(FIX::CustOrderHandlingInst(custOrderHandlingInst));
            orderCancelReplaceRequest.setField(FIX::OrdType(ordType));
            orderCancelReplaceRequest.setField(FIX::OrigClOrdID(origClOrdID));
            if(ordType == FIX::OrdType_LIMIT || ordType == FIX::OrdType_STOP_LIMIT)
                orderCancelReplaceRequest.setField(FIX::Price(price));
            orderCancelReplaceRequest.setField(FIX::Side(side));
            orderCancelReplaceRequest.setField(FIX::TimeInForce(timeInForce));
            orderCancelReplaceRequest.setField(FIX::ManualOrderIndicator(manualOrderIndicator));
            orderCancelReplaceRequest.setField(FIX::TransactTime());
            if(ordType == FIX::OrdType_STOP || ordType == FIX::OrdType_STOP_LIMIT)
                orderCancelReplaceRequest.setField(FIX::StopPx(stopPx));
            orderCancelReplaceRequest.setField(FIX::SecurityDesc(securityDesc));
            if(timeInForce == FIX::TimeInForce_IMMEDIATE_OR_CANCEL) //FAK
                orderCancelReplaceRequest.setField(FIX::MinQty(minQty));
            orderCancelReplaceRequest.setField(FIX::SecurityType(securityType));
            orderCancelReplaceRequest.setField(FIX::CustomerOrFirm(customerOrFirm));
            if(timeInForce != FIX::TimeInForce_IMMEDIATE_OR_CANCEL)//FAK
                orderCancelReplaceRequest.setField(FIX::MaxShow(maxShow));
            if(timeInForce == FIX::TimeInForce_GOOD_TILL_DATE)
                orderCancelReplaceRequest.setField(FIX::ExpireDate(expireDate));
            orderCancelReplaceRequest.setField(9702, "1");//CTiCode
            orderCancelReplaceRequest.setField(9717, clOrdID);//CorrelationClOrdID

            if(IFMFlag == 'Y')
                orderCancelReplaceRequest.setField(9768, std::string(1, IFMFlag));

            if(cmtaGiveupCD == "GU" || cmtaGiveupCD == "SX"){//give up
                orderCancelReplaceRequest.setField(FIX::NoAllocs(1));
                orderCancelReplaceRequest.setField(FIX::AllocAccount(allocAccount));
                orderCancelReplaceRequest.setField(9708, cmtaGiveupCD);
                orderCancelReplaceRequest.setField(9707, giveUpFirm);
            }
            Session::sendToTarget(orderCancelReplaceRequest, sessionID);

            return true;
        }

        bool CMEApplication::sendOrderStatusRequest(const SessionID &sessionID,
                                                    std::string clOrdID,
                                                    std::string orderID,
                                                    char side,
                                                    std::string securityDesc,
                                                    std::string securityType,
                                                    std::string correlationClOrdID,
                                                    bool manualOrderIndicator) {
            if(!this->isSessionLoggedOn(sessionID)){
                return false;
            }

            FIX42::OrderStatusRequest orderStatusRequest;
            orderStatusRequest.setField(FIX::ClOrdID(clOrdID));
            orderStatusRequest.setField(FIX::OrderID(orderID));
            orderStatusRequest.setField(FIX::Side(side));
            orderStatusRequest.setField(FIX::ManualOrderIndicator(manualOrderIndicator));
            orderStatusRequest.setField(FIX::TransactTime());
            orderStatusRequest.setField(FIX::SecurityDesc(securityDesc));
            orderStatusRequest.setField(FIX::SecurityType(securityType));
            orderStatusRequest.setField(9717, correlationClOrdID); //CorrelationClOrdID

            Session::sendToTarget(orderStatusRequest, sessionID);

            return true;
        }

        bool CMEApplication::sendOrderMassStatusReport(const SessionID &sessionID,
                                                       std::string massStatusReqID,
                                                       int32_t massStatusReqType,
                                                       int32_t marketSegmentID,
                                                       int32_t ordStatusReqType,
                                                       std::string account,
                                                       std::string symbol,
                                                       std::string securityDesc,
                                                       char timeInForce,
                                                       bool manualOrderIndicator) {
            if(!this->isSessionLoggedOn(sessionID)){
                return false;
            }

            FIX44::OrderMassStatusRequest orderMassStatusRequest;
            orderMassStatusRequest.setField(FIX::MassStatusReqID(massStatusReqID));
            orderMassStatusRequest.setField(FIX::MassStatusReqType(massStatusReqType));
            if(massStatusReqType == 100)
                orderMassStatusRequest.setField(FIX::MarketSegmentID(std::to_string(marketSegmentID)));
            if(ordStatusReqType == 100 || ordStatusReqType == 101)
                orderMassStatusRequest.setField(5000, std::to_string(ordStatusReqType)); //OrdStatusReqType
            if(ordStatusReqType == 101)
                orderMassStatusRequest.setField(FIX::Account(account));
            if(massStatusReqType == 3)
                orderMassStatusRequest.setField(FIX::Symbol(symbol));
            else if(massStatusReqType == 1)
                orderMassStatusRequest.setField(FIX::SecurityDesc(securityDesc));

            if(timeInForce != 'N')
                orderMassStatusRequest.setField(FIX::TimeInForce(timeInForce));

            orderMassStatusRequest.setField(FIX::TransactTime());
            orderMassStatusRequest.setField(FIX::ManualOrderIndicator(manualOrderIndicator));

            orderMassStatusRequest.getHeader().setField(FIX::BeginString("FIX.4.2"));
            Session::sendToTarget(orderMassStatusRequest, sessionID);
            return true;
        }

        bool CMEApplication::sendQuoteRequest(const SessionID &sessionID,
                                              std::string quoteReqID,
                                              std::string symbol,
                                              int32_t orderQty,
                                              char side,
                                              std::string securityDesc,
                                              std::string securityType,
                                              std::string custOrderHandlingInst,
                                              bool manualOrderIndicator) {
            if(!this->isSessionLoggedOn(sessionID)){
                return false;
            }

            FIX42::QuoteRequest quoteRequest;

            quoteRequest.setField(FIX::QuoteReqID(quoteReqID));
            quoteRequest.setField(FIX::NoRelatedSym(1));
            quoteRequest.setField(FIX::Symbol(symbol));
            if(side == FIX::Side_BUY || side == FIX::Side_SELL)
                quoteRequest.setField(FIX::OrderQty(orderQty));
            quoteRequest.setField(FIX::Side(side));
            quoteRequest.setField(FIX::TransactTime());
            quoteRequest.setField(FIX::SecurityDesc(securityDesc));
            quoteRequest.setField(FIX::QuoteType(1));
            quoteRequest.setField(FIX::ManualOrderIndicator(manualOrderIndicator));
            quoteRequest.setField(FIX::CustOrderHandlingInst(custOrderHandlingInst));

            Session::sendToTarget(quoteRequest, sessionID);
            return true;
        }

        //Norman UDS
        bool CMEApplication::sendSecurityDefinitionRequest(const SessionID& sessionID,
                                                           bool manualOrderIndicator,
                                                           std::string securityReqID,
                                                           std::string securitySubType,
                                                           int32_t noLegs,
                                                           int32_t legOptionSize,
                                                           std::vector<LegOption> legOption,
                                                           int32_t legFutureSize,
                                                           std::vector<LegFuture> legFuture
                                                           ){
            if(!this->isSessionLoggedOn(sessionID)){
                return false;
            }

            FIX42::SecurityDefinitionRequest securityDefinitionRequest;

            securityDefinitionRequest.setField(FIX::ManualOrderIndicator(manualOrderIndicator));
            securityDefinitionRequest.setField(FIX::SecurityReqID(securityReqID));
            securityDefinitionRequest.setField(FIX::SecuritySubType(securitySubType));
            securityDefinitionRequest.setField(FIX::NoLegs(noLegs));
            securityDefinitionRequest.setField(FIX::SecurityRequestType(1));

            FIX42::SecurityDefinitionRequest::NoRelatedSym group;
            //Add the fields for option group
            for (int i=0; i<legOptionSize; i++){
                group.setField(FIX::LegSymbol(legOption[i].legSymbol_));
                group.setField(FIX::LegSecurityDesc(legOption[i].legSecurityDesc_));
                group.setField(FIX::LegRatioQty(legOption[i].legRatioQty_));
                group.setField(FIX::LegSide(legOption[i].legSide_));
                securityDefinitionRequest.addGroup(group);
            }
            //Add the fields for Future group
            for (int i=0; i<legFutureSize; i++){
                group.setField(FIX::LegSymbol(legFuture[i].legSymbol_));
                group.setField(FIX::LegSecurityDesc(legFuture[i].legSecurityDesc_));
                group.setField(FIX::LegPrice(legFuture[i].legPrice_));
                group.setField(FIX::LegOptionRatio(legFuture[i].legOptionRatio_));
                group.setField(FIX::LegSide(legFuture[i].legSide_));
                securityDefinitionRequest.addGroup(group);
            }

            Session::sendToTarget(securityDefinitionRequest, sessionID);
            return true;
        }

        bool CMEApplication::sendQuoteCancel(const SessionID &sessionID,
                                             std::string quoteID,
                                             int32_t quoteCancelType,
                                             bool manualOrderIndicator,
                                             int32_t noQuoteEntries,
                                             const std::vector<QuoteCancelEntry> &quoteCancelEntries) {
            if(!this->isSessionLoggedOn(sessionID)){
                return false;
            }
            FIX42::QuoteCancel quoteCancel;

            quoteCancel.setField(FIX::QuoteID(quoteID));
            quoteCancel.setField(FIX::QuoteCancelType(quoteCancelType));
            quoteCancel.setField(FIX::ManualOrderIndicator(manualOrderIndicator));
            quoteCancel.setField(FIX::NoQuoteEntries(noQuoteEntries));

            for(int32_t i = 0; i < noQuoteEntries; ++i) {
                FIX42::QuoteCancel::NoQuoteEntries group;
                if (quoteCancelType == FIX::QuoteCancelType_CANCEL_ALL_QUOTES) {
                    group.setField(FIX::Symbol("N/A"));
                } else {
                    group.setField(FIX::Symbol(quoteCancelEntries[i].symbol_));
                };

                if (quoteCancelType == FIX::QuoteCancelType_CANCEL_FOR_SYMBOL) {
                    group.setField(FIX::SecurityDesc(quoteCancelEntries[i].securityDesc_));
                }

                if (quoteCancelType == 100){//Cancel per quote set
                    group.setField(FIX::QuoteSetID(quoteCancelEntries[i].quoteSetID_));
                };
                quoteCancel.addGroup(group);
            }

            Session::sendToTarget(quoteCancel, sessionID);
            return true;
        }
        bool CMEApplication::sendMassQuote(const SessionID &sessionID,
                                           std::string quoteReqID,
                                           std::string quoteID,
                                           std::string MMAccount,
                                           bool manualOrderIndicator,
                                           std::string custOrderHandlingInst,
                                           int32_t customerOrFirm,
                                           int32_t NoQuoteSets,
                                           const std::vector<QuoteSet>& quoteSet) {
            if(!this->isSessionLoggedOn(sessionID)){
                return false;
            }
            FIX42::MassQuote massQuote;

            if(!quoteReqID.empty())
                massQuote.setField(FIX::QuoteReqID(quoteReqID));

            massQuote.setField(FIX::QuoteID(quoteID));
            massQuote.setField(9771, MMAccount);//MMAccount
            massQuote.setField(FIX::ManualOrderIndicator(manualOrderIndicator));
            massQuote.setField(FIX::CustOrderHandlingInst(custOrderHandlingInst));
            massQuote.setField(FIX::CustomerOrFirm(customerOrFirm));
            massQuote.setField(9702, "1");//CTiCode
            massQuote.setField(FIX::NoQuoteSets(NoQuoteSets));

            for(int32_t i = 0; i < NoQuoteSets; ++i){
                FIX42::MassQuote::NoQuoteSets group;

                group.setField(FIX::QuoteSetID(quoteSet[i].quoteSetID_));
                if(!quoteSet[i].underlyingSecurityDesc_.empty())
                    group.setField(FIX::UnderlyingSecurityDesc(quoteSet[i].underlyingSecurityDesc_));

                group.setField(FIX::TotQuoteEntries(quoteSet[i].NoQuoteEntries_));//same as NoQuoteEntries
                group.setField(FIX::NoQuoteEntries(quoteSet[i].NoQuoteEntries_));

                for(int32_t j = 0; j < quoteSet[i].NoQuoteEntries_; ++j){
                    FIX42::MassQuote::NoQuoteSets::NoQuoteEntries entrygroup;
                    entrygroup.setField(FIX::QuoteEntryID(quoteSet[i].quoteEntries_[j].quoteEntryID_));
                    entrygroup.setField(FIX::Symbol(quoteSet[i].quoteEntries_[j].symbol_));
                    entrygroup.setField(FIX::SecurityType(quoteSet[i].quoteEntries_[j].securityType_));
                    if(!quoteSet[i].quoteEntries_[j].securityID_){
                        entrygroup.setField(FIX::SecurityID(std::to_string(quoteSet[i].quoteEntries_[j].securityID_)));
                        entrygroup.setField(FIX::SecurityIDSource("8")); //Exchange symbol
                    }
                    entrygroup.setField(FIX::TransactTime());
                    if(!quoteSet[i].quoteEntries_[j].bidPx_){
                        entrygroup.setField(FIX::BidPx(quoteSet[i].quoteEntries_[j].bidPx_));
                        entrygroup.setField(FIX::BidSize(quoteSet[i].quoteEntries_[j].bidSize_));
                    }
                    if(!quoteSet[i].quoteEntries_[j].offerPx_){
                        entrygroup.setField(FIX::OfferPx(quoteSet[i].quoteEntries_[j].offerPx_));
                        entrygroup.setField(FIX::OfferSize(quoteSet[i].quoteEntries_[j].offerSize_));
                    }
                    group.addGroup(entrygroup);
                }
                massQuote.addGroup(group);
            }

            Session::sendToTarget(massQuote, sessionID);
            return true;
        }

        bool CMEApplication::sendOrderMassActionRequest(const SessionID &sessionID,
                                                        std::string clOrdID,
                                                        int32_t massActionScope,
                                                        int32_t marketSegmentID,
                                                        std::string symbol,
                                                        std::string securityDesc,
                                                        int32_t massCancelRequestType,
                                                        std::string account,
                                                        char side,
                                                        char ordType,
                                                        char timeInForce,
                                                        bool manualOrderIndicator) {
            if(!this->isSessionLoggedOn(sessionID)){
                return false;
            }

            FIX50SP2::OrderMassActionRequest orderMassActionRequest;

            orderMassActionRequest.setField(FIX::ClOrdID(clOrdID));
            orderMassActionRequest.setField(FIX::MassActionType(3));//cancel
            orderMassActionRequest.setField(FIX::MassActionScope(massActionScope));
            if(massActionScope == FIX::MassActionScope_ALL_ORDERS_FOR_A_MARKET_SEGMENT){
                orderMassActionRequest.setField(FIX::MarketSegmentID(std::to_string(marketSegmentID)));
            }
            else if(massActionScope == FIX::MassActionScope_ALL_ORDERS_FOR_A_SECURITY_GROUP) {
                orderMassActionRequest.setField(FIX::Symbol(symbol));
            }
            else if(massActionScope == FIX::MassActionScope_ALL_ORDERS_FOR_A_SECURITY){
                orderMassActionRequest.setField(FIX::SecurityDesc(securityDesc));
            }
            if(massCancelRequestType == 100 || massCancelRequestType == 101)
                orderMassActionRequest.setField(6115, std::to_string(massCancelRequestType)); //MassCancelRequestType
            if(massCancelRequestType == 101)
                orderMassActionRequest.setField(FIX::Account(account));

            if(side == FIX::Side_SELL || side == FIX::Side_BUY)
                orderMassActionRequest.setField(FIX::Side(side));
            if(ordType == FIX::OrdType_LIMIT || ordType == FIX::OrdType_STOP_LIMIT)
                orderMassActionRequest.setField(FIX::OrdType(ordType));

            if(timeInForce != 'N')
                orderMassActionRequest.setField(FIX::TimeInForce(timeInForce));
            orderMassActionRequest.setField(FIX::TransactTime());
            orderMassActionRequest.setField(FIX::ManualOrderIndicator(manualOrderIndicator));

            orderMassActionRequest.getHeader().setField(FIX::BeginString("FIX.4.2"));
            Session::sendToTarget(orderMassActionRequest, sessionID);
            return true;
        }

        bool CMEApplication::sendNewOrderCross(const SessionID &sessionID,
                                               double price,
                                               std::string symbol,
                                               bool manualOrderIndicator,
                                               std::string securityDesc,
                                               std::string securityType,
                                               std::string crossID,
                                               const std::vector<CrossEntry> &crossEntries) {
            if(!this->isSessionLoggedOn(sessionID) || crossEntries.size() != 2){
                return false;
            }

            FIX44::NewOrderCross newOrderCross;

            newOrderCross.setField(FIX::HandlInst('1'));
            newOrderCross.setField(FIX::SecurityIDSource("8"));
            newOrderCross.setField(FIX::OrdType('2'));
            newOrderCross.setField(FIX::Price(price));
            newOrderCross.setField(FIX::Symbol(symbol));
            newOrderCross.setField(FIX::TransactTime());
            newOrderCross.setField(FIX::ManualOrderIndicator(manualOrderIndicator));
            newOrderCross.setField(FIX::SecurityDesc(securityDesc));
            newOrderCross.setField(FIX::SecurityType(securityType));
            newOrderCross.setField(FIX::CrossID(crossID));
            newOrderCross.setField(FIX::CrossType(3));
            newOrderCross.setField(FIX::CrossPrioritization(0));
            newOrderCross.setField(FIX::TransBkdTime());
            newOrderCross.setField(FIX::NoSides(2));

            for(int32_t i = 0; i < crossEntries.size(); ++i){
                FIX44::NewOrderCross::NoSides side;

                side.setField(FIX::Side(crossEntries[i].side_));
                side.setField(FIX::Account(crossEntries[i].account_));
                side.setField(FIX::ClOrdID(crossEntries[i].clOrdID_));
                side.setField(FIX::CustOrderHandlingInst(crossEntries[i].custOrderHandlingInst_));
                side.setField(FIX::OrderQty(crossEntries[i].orderQty_));
                side.setField(FIX::SideTimeInForce(crossEntries[i].sideTimeInForce_));
                side.setField(FIX::CustomerOrFirm(crossEntries[i].customerOrFirm_));
                side.setField(9702, "1"); // CtiCode

                newOrderCross.addGroup(side);
            }
            newOrderCross.getHeader().setField(FIX::BeginString("FIX.4.2"));

            return true;
        }
    } //namespace cme
} //namespace falcon