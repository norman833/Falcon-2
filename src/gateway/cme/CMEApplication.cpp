#include "CMEApplication.h"

namespace falcon {
    namespace cme {
        using  namespace FIX;

        void CMEApplication::onCreate(const SessionID &) {

        };

        void CMEApplication::onLogon(const SessionID &) {

        };

        void CMEApplication::onLogout(const SessionID &) {

        };

        void CMEApplication::fromApp(const Message &, const SessionID &)
            throw( FieldNotFound, IncorrectDataFormat, IncorrectTagValue, UnsupportedMessageType ) {

        };

        void CMEApplication::fromAdmin(const Message &, const SessionID &)
            throw( FieldNotFound, IncorrectDataFormat, IncorrectTagValue, RejectLogon ) {

        };

        void CMEApplication::toApp(Message &, const SessionID &) throw( DoNotSend ) {

        };

        void CMEApplication::toAdmin(Message &, const SessionID &) {

        }
    } //namespace cme
} //namespace falcon