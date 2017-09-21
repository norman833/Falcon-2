#ifndef FALCON_CMEQFCLIENT_H
#define FALCON_CMEQFCLIENT_H

#include <cstdint>

#include "quickfix/Application.h"
#include "quickfix/SessionID.h"
#include "quickfix/MessageCracker.h"
#include "quickfix/FileStore.h"
#include "quickfix/FileLog.h"
#include "quickfix/Session.h"
#include "quickfix/SessionSettings.h"
#include "quickfix/SocketInitiator.h"
#include "quickfix/Message.h"

namespace falcon {
    namespace cme {
        using namespace FIX;

        class CMEApplication : public Application, MessageCracker {
        public:
            CMEApplication(std::string settingFile);
            virtual bool start();
            virtual bool stop(bool force);
            virtual SessionID getSessionIDbyTargetCompID(const std::string);

            virtual void onCreate( const SessionID& );
            virtual void onLogon( const SessionID& );
            virtual void onLogout( const SessionID& );
            virtual void toAdmin( Message&, const SessionID& );
            virtual void toApp( Message&, const SessionID& ) throw( DoNotSend );
            virtual void fromAdmin( const Message&, const SessionID& )
                throw( FieldNotFound, IncorrectDataFormat, IncorrectTagValue, RejectLogon );
            virtual void fromApp( const Message&, const SessionID& )
                throw( FieldNotFound, IncorrectDataFormat, IncorrectTagValue, UnsupportedMessageType );

            virtual void onMessage(const FIX42::TestRequest&, const SessionID&);
            virtual void onMessage(const FIX42::BusinessMessageReject&, const SessionID&);
            virtual void onMessage(const FIX42::ExecutionReport&, const SessionID&);
            virtual void onMessage(const FIX42::OrderCancelReject&, const SessionID&);

            virtual bool sendTestRequest(const SessionID&, const std::string);
            virtual bool sendOrderCancelRequest(const SessionID&);
            virtual bool sendOrderCancelReplaceRequest(const SessionID&);
            virtual bool sendNewOrderSingle(const SessionID&);
            virtual bool sendOrderStatusRequest(const SessionID&);

        private:
            virtual void setCMEHeader(Message&, const SessionID&);
            virtual void setLogon(Message&, const SessionID&);
            virtual void setLogout(Message&, const SessionID&);
            SessionSettings settings_;
            FileStoreFactory storeFactory_;
            FileLogFactory logFactory_;
            SocketInitiator socketInitiator_;
        };
    } //namespace cme
} //namespace falcon

#endif //FALCON_CMEQFCLIENT_H
