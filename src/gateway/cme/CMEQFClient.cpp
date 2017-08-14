#include "CMEQFClient.h"

namespace falcon {
    namespace cme {
        using  namespace FIX;

        void CMEQFClient::onCreate(const SessionID &) {

        };

        void CMEQFClient::onLogon(const SessionID &) {

        };

        void CMEQFClient::onLogout(const SessionID &) {

        };

        void CMEQFClient::fromApp(const Message &, const SessionID &)
            throw( FieldNotFound, IncorrectDataFormat, IncorrectTagValue, UnsupportedMessageType ) {

        };

        void CMEQFClient::fromAdmin(const Message &, const SessionID &)
            throw( FieldNotFound, IncorrectDataFormat, IncorrectTagValue, RejectLogon ) {

        };

        void CMEQFClient::toApp(Message &, const SessionID &) throw( DoNotSend ) {

        };

        void CMEQFClient::toAdmin(Message &, const SessionID &) {

        }
    } //namespace cme
} //namespace falcon