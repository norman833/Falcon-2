#include <sstream>
#include "CMEApplication.h"
#include "Logger.h"

#include "quickfix/fix42/NewOrderSingle.h"
#include "quickfix/fix42/TestRequest.h"
#include "quickfix/fix42/Heartbeat.h"
#include "quickfix/fix42/OrderCancelRequest.h"
#include "quickfix/fix42/ExecutionReport.h"
#include "quickfix/fix42/OrderStatusRequest.h"
#include "quickfix/fix42/OrderCancelReplaceRequest.h"
#include "quickfix/fix42/QuoteRequest.h"
#include "quickfix/fix42/SecurityDefinitionRequest.h"
#include "quickfix/fix42/QuoteCancel.h"
#include "quickfix/fix44/OrderMassStatusRequest.h"
#include "quickfix/fix42/MassQuote.h"
#include "quickfix/fix50sp2/OrderMassActionRequest.h"

namespace falcon {
    namespace cme {
        using  namespace FIX;

        CMEApplication::CMEApplication(std::string settingFile) :
                settings_(settingFile), storeFactory_(settings_), logFactory_(settings_),
                socketInitiator_(*this, storeFactory_, settings_, logFactory_){
            LOG("creating CME session...");
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

            LOG(sstream.str());

            auto msgSeqNum = message.getHeader().getField(FIX::FIELD::MsgSeqNum);
            std::lock_guard<std::mutex> guard(this->latestSeqNO_mutex);
            this->latestSeqNo = atol(msgSeqNum.c_str());
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
                if(this->latestSeqNo - beginSeqNo >= 2500)
                message.setField(FIX::EndSeqNo(beginSeqNo + 2499));
            }
        }

        void CMEApplication::onMessage(const FIX42::BusinessMessageReject &message, const SessionID &sessionID) {


        }
        void CMEApplication::onMessage(const FIX42::OrderCancelReject &, const SessionID &) {

        }

        void CMEApplication::onMessage(const FIX42::QuoteAcknowledgement &quoteAcknowledgement, const SessionID& sessionID) {

        }

        void CMEApplication::onMessage(const FIX42::ExecutionReport &executionReport, const SessionID &sessionID) {
            auto execType = executionReport.getField(FIX::FIELD::ExecType);

            if(execType == 'I') {////Order Status Request Acknowledgment

            }
            else if(execType == '0' || execType == '4' || execType == '5'){ //Order Creation Cancel Modification

            }
            else if(execType == '1' || execType == '2'){//Order Fill

            }
            else if(execType == 'C'){//Order Elimination

            }
            else if(execType == '8'){//Reject

            }
            else if(execType == 'H'){//Trade Cancel

            }
            else{
                std::stringstream sstream;
                sstream << "Unexpected execution report with execType " << execType << "\n";
                LOG_ERR(sstream.str());
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
            auto lastMsgSeqNumProcessed = socketInitiator_.getSession(sessionID)->getExpectedTargetNum()-1;
            auto targetSubID = settings_.get(sessionID).getString("TargetSubID");
            auto senderSubID = settings_.get(sessionID).getString("SenderSubID");
            auto senderLocationID = settings_.get(sessionID).getString("SenderLocationID");

            message.getHeader().setField(FIX::LastMsgSeqNumProcessed(lastMsgSeqNumProcessed));
            message.getHeader().setField(FIX::TargetSubID(targetSubID));
            message.getHeader().setField(FIX::SenderSubID(senderSubID));
            message.getHeader().setField(FIX::SenderLocationID(senderLocationID));
        }

        void CMEApplication::setLogon(Message &message, const SessionID &sessionID) {

            auto password = settings_.get(sessionID).getString("RawData");
            auto rawDatalength = password.length();
            auto applicationSystemName = settings_.get(sessionID).getString("ApplicationSystemName");
            auto tradingSystemVersion = settings_.get(sessionID).getString("TradingSystemVersion");
            auto applicationSystemVendor = settings_.get(sessionID).getString("ApplicationSystemVendor");

            message.setField(FIX::RawData(password));
            message.setField(FIX::RawDataLength(rawDatalength));
            message.setField(1603, applicationSystemName);
            message.setField(1604, tradingSystemVersion);
            message.setField(1605, applicationSystemVendor);
        }

        void CMEApplication::setLogout(Message &message, const SessionID &sessionID) {
            FIX::MsgSeqNum msgSeqNum;
            message.getHeader().getField(msgSeqNum);

            message.setField(789, msgSeqNum.getString());//NextExpectedMsgSeqNum
        }

        bool CMEApplication::isSessionLoggedOn(const SessionID &sessionID) {
            return(this->socketInitiator_.getSession(sessionID)->isLoggedOn());
        }

        bool CMEApplication::sendTestRequest(const SessionID &sessionID, const std::string testRequestID) {
            if(!this->isSessionLoggedOn(sessionID)){
                return false;
            }

            FIX42::TestRequest testRequest;
            testRequest.setField(FIX::TestReqID(testRequestID));
            Session::sendToTarget(testRequest, sessionID);

            return  true;
        }

        bool CMEApplication::sendOrderCancelRequest(const SessionID &sessionID,
                                                    const std::string account,
                                                    const std::string clOrdID,
                                                    const std::string orderID,
                                                    const std::string origClOrdID,
                                                    const char side,
                                                    const std::string securityDesc,
                                                    const std::string securityType,
                                                    const std::string correlationClOrdID,
                                                    const bool manualOrderIndicator) {

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
                                                const std::string account,
                                                const std::string clOrdID,
                                                const std::string custOrderHandlingInst,
                                                const int32_t orderQty,
                                                const char ordType,
                                                const double price,
                                                const char side,
                                                //const std::string symbol,
                                                const char timeInForce,
                                                const double stopPx,
                                                const std::string securityDesc,
                                                const int32_t minQty,
                                                const std::string securityType,
                                                const int32_t customerOrFirm,
                                                const int32_t maxShow,
                                                const std::string expireDate,
                                                const bool manualOrderIndicator) {
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

            Session::sendToTarget(newOrderSingle, sessionID);

            return true;
        }

        bool CMEApplication::sendOrderCancelReplaceRequest(const SessionID &sessionID,
                                                           const std::string account,
                                                           const std::string clOrdID,
                                                           const std::string orderID,
                                                           const int32_t orderQty,
                                                           const std::string custOrderHandlingInst,
                                                           const char ordType,
                                                           const std::string origClOrdID,
                                                           const double price,
                                                           const char side,
                                                           const char timeInForce,
                                                           const bool manualOrderIndicator,
                                                           const double stopPx,
                                                           const std::string securityDesc,
                                                           const int32_t minQty,
                                                           const std::string securityType,
                                                           const int32_t customerOrFirm,
                                                           const int32_t maxShow,
                                                           const std::string expireDate,
                                                           const std::string correlationClOrdID,
                                                           const char IFMFlag) {
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
            Session::sendToTarget(orderCancelReplaceRequest, sessionID);

            return true;
        }

        bool CMEApplication::sendOrderStatusRequest(const SessionID &sessionID,
                                                    const std::string clOrdID,
                                                    const std::string orderID,
                                                    const char side,
                                                    const std::string securityDesc,
                                                    const std::string securityType,
                                                    const std::string correlationClOrdID,
                                                    const bool manualOrderIndicator) {
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
                                                       const std::string massStatusReqID,
                                                       const int32_t massStatusReqType,
                                                       const int32_t marketSegmentID,
                                                       const int32_t ordStatusReqType,
                                                       const std::string account,
                                                       const std::string symbol,
                                                       const std::string securityDesc,
                                                       const char timeInForce,
                                                       const bool manualOrderIndicator) {
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
                                              const std::string quoteReqID,
                                              const std::string symbol,
                                              const int32_t orderQty,
                                              const char side,
                                              const std::string securityDesc,
                                              const std::string securityType,
                                              const std::string custOrderHandlingInst,
                                              const bool manualOrderIndicator) {
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

        bool CMEApplication::sendMassQuote(const SessionID &sessionID,
                                           FIX42::MassQuote &massQuote) {
            if(!this->isSessionLoggedOn(sessionID)){
                return false;
            }

            Session::sendToTarget(massQuote, sessionID);
            return true;
        }

        bool CMEApplication::sendQuoteCancel(const SessionID &sessionID,
                                             FIX42::QuoteCancel &quoteCancel) {
            if(!this->isSessionLoggedOn(sessionID)){
                return false;
            }

            Session::sendToTarget(quoteCancel, sessionID);
            return true;
        }

        bool CMEApplication::sendOrderMassActionRequest(const SessionID &sessionID,
                                                        const std::string clOrdID,
                                                        const int32_t massActionScope,
                                                        const int32_t marketSegmentID,
                                                        const std::string symbol,
                                                        const std::string securityDesc,
                                                        const int32_t massCancelRequestType,
                                                        const std::string account,
                                                        const char side,
                                                        const char ordType,
                                                        const char timeInForce,
                                                        const bool manualOrderIndicator) {
            if(!this->isSessionLoggedOn(sessionID)){
                return false;
            }

            FIX50SP2::OrderMassActionRequest orderMassActionRequest;

            orderMassActionRequest.getHeader().setField(FIX::BeginString("FIX.4.2"));
            Session::sendToTarget(orderMassActionRequest, sessionID);
            return true;
        }

    } //namespace cme
} //namespace falcon