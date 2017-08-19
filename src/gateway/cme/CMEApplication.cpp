#include "CMEApplication.h"
#include "quickfix/fix42/NewOrderSingle.h"

namespace falcon {
    namespace cme {
        using  namespace FIX;

        void CMEApplication::onCreate(const SessionID &sessionID) {
        };

        void CMEApplication::onLogon(const SessionID &sessionID) {

        };

        void CMEApplication::onLogout(const SessionID &sessionID) {

        };

        void CMEApplication::fromApp(const Message &message, const SessionID &sessionID)
            throw( FieldNotFound, IncorrectDataFormat, IncorrectTagValue, UnsupportedMessageType ) {
                this->crack(message, sessionID);
        };

        void CMEApplication::fromAdmin(const Message &message, const SessionID &sessionID)
            throw( FieldNotFound, IncorrectDataFormat, IncorrectTagValue, RejectLogon ) {

        };

        void CMEApplication::toApp(Message &message, const SessionID &sessionID) throw( DoNotSend ) {

        };

        void CMEApplication::toAdmin(Message &message, const SessionID &sessionID) {
            //std::cout << sessionID.toString() << message.toString() << std::endl;
            if (FIX::MsgType_Logon == message.getHeader().getField(FIX::FIELD::MsgType)){
                std::cout << "Logon sent" << std::endl;
            }

        }

        void CMEApplication::onMessage(const FIX42::NewOrderSingle &message, const FIX::SessionID &sessionID) {
            FIX::ClOrdID clOrdID;
            message.get(clOrdID);

            FIX::ClearingAccount clearingAccount;
            message.get(clearingAccount);
            std::cout << "NewOrderSingle " << clOrdID << " " << clearingAccount << std::endl;
        }
    } //namespace cme
} //namespace falcon