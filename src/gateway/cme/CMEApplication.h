#ifndef FALCON_CMEQFCLIENT_H
#define FALCON_CMEQFCLIENT_H

#include "quickfix/Application.h"
#include "quickfix/SessionID.h"

namespace falcon {
    namespace cme {
        using namespace FIX;

        class CMEApplication : public Application {
        public:
            virtual void onCreate( const SessionID& );
            virtual void onLogon( const SessionID& );
            virtual void onLogout( const SessionID& );
            virtual void toAdmin( Message&, const SessionID& );
            virtual void toApp( Message&, const SessionID& ) throw( DoNotSend );
            virtual void fromAdmin( const Message&, const SessionID& )
                throw( FieldNotFound, IncorrectDataFormat, IncorrectTagValue, RejectLogon );
            virtual void fromApp( const Message&, const SessionID& )
                throw( FieldNotFound, IncorrectDataFormat, IncorrectTagValue, UnsupportedMessageType );
        private:
        };
    } //namespace cme
} //namespace falcon

#endif //FALCON_CMEQFCLIENT_H
