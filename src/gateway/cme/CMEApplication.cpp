#include <sstream>
#include "CMEApplication.h"
#include "Logger.h"

#include "quickfix/fix42/NewOrderSingle.h"
#include "quickfix/fix42/TestRequest.h"
#include "quickfix/fix42/Heartbeat.h"
#include "quickfix/fix42/OrderCancelRequest.h"
#include "quickfix/fix42/NewOrderSingle.h"
#include "quickfix/fix42/ExecutionReport.h"

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
                if(rit->getSenderCompID() == targetCompID){
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
                std::cout << "Heartbeat sent " << std::endl;
            }
        }

        void CMEApplication::onMessage(const FIX42::BusinessMessageReject &message, const SessionID &sessionID) {


        }
        void CMEApplication::onMessage(const FIX42::OrderCancelReject &, const SessionID &) {

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

        bool CMEApplication::sendTestRequest(const SessionID &sessionID, const std::string testRequestID) {
            if(!this->socketInitiator_.getSession(sessionID)->isLoggedOn()){
                return false;
            }

            FIX42::TestRequest testRequest;
            testRequest.setField(FIX::TestReqID(testRequestID));
            Session::sendToTarget(testRequest, sessionID);

            return  true;
        }
        bool CMEApplication::sendOrderCancelRequest(const SessionID &sessionID) {

            if(!this->socketInitiator_.getSession(sessionID)->isLoggedOn()){
                return false;
            }

            FIX42::OrderCancelRequest orderCancelRequest;


            //orderCancelRequest.

            return true;
        }

        bool CMEApplication::sendNewOrderSingle(const SessionID &sessionID) {
            if(!this->socketInitiator_.getSession(sessionID)->isLoggedOn()){
                return false;
            }

            FIX42::NewOrderSingle newOrderSingle;
            //account
            //client order id
            newOrderSingle.setField(FIX::HandlInst('1'));
            newOrderSingle.isSetField(FIX::CustOrderHandlingInst("Y"));
            //OrderQty
            //OrderType
            //Price
            //Side
            //Symbol
            //TimeInforce
            //TransactTime
            //ManualOrderIndicator
            //FIX::ManualOrderIndicator(true);
            return true;
        }

        bool CMEApplication::sendOrderCancelReplaceRequest(const SessionID &sessionID) {

            return true;
        }

        bool CMEApplication::sendOrderStatusRequest(const SessionID &sessionID) {

            return true;
        }
    } //namespace cme
} //namespace falcon