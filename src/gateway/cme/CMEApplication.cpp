#include "CMEApplication.h"
#include "Logger.h"

#include "quickfix/fix42/NewOrderSingle.h"
#include "quickfix/fix42/TestRequest.h"
#include "quickfix/fix42/Heartbeat.h"
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
        }
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
            if(msgType == FIX::MsgType_Heartbeat) {
                std::cout << "Heartbeat sent " << std::endl;
            }
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
                std::cout << "Logon sent" << std::endl;
            }
            else if(msgType == FIX::MsgType_Heartbeat){
                std::cout << "Heartbeat sent " << std::endl;
            }
        }

        void CMEApplication::onMessage(const FIX42::NewOrderSingle &message, const FIX::SessionID &sessionID) {
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
    } //namespace cme
} //namespace falcon