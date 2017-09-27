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
            virtual void onMessage(const FIX42::QuoteAcknowledgement&);

            virtual bool sendTestRequest(const SessionID&, const std::string);
            virtual bool sendOrderCancelRequest(const SessionID& sessionID,
                                                const std::string account,
                                                const std::string clOrdID,
                                                const std::string orderID,
                                                const std::string origClOrdID,
                                                const char side,
                                                const std::string securityDesc,
                                                const std::string securityType,
                                                const std::string correlationClOrdID,
                                                const bool manualOrderIndicator
            );
            virtual bool sendOrderCancelReplaceRequest(const SessionID& sessionID,
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
                                                       const std::string correlationClOrdID
            );
            virtual bool sendNewOrderSingle(const SessionID& sessionID,
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
                                            const bool manualOrderIndicator
            );
            virtual bool sendOrderStatusRequest(const SessionID& sessionID,
                                                const std::string clOrdID,
                                                const std::string orderID,
                                                const char side,
                                                const std::string securityDesc,
                                                const std::string securityType,
                                                const std::string correlationClOrdID,
                                                const bool manualOrderIndicator
            );

            virtual bool sendOrderMassStatusReport(const SessionID& sessionID,
                                                   const std::string massStatusReqID,
                                                   const int32_t massStatusReqType,
                                                   const int32_t marketSegmentID,
                                                   const int32_t ordStatusReqType,
                                                   const std::string account,
                                                   const std::string symbol,
                                                   const std::string securityDesc,
                                                   const char timeInForce,
                                                   const bool manualOrderIndicator
            );

            virtual bool sendQuoteRequest(const SessionID& sessionID,
                                          const std::string quoteReqID,
                                          const std::string symbol,
                                          const int32_t orderQty,
                                          const char side,
                                          const std::string securityDesc,
                                          const std::string securityType,
                                          const std::string custOrderHandlingInst,
                                          const bool manualOrderIndicator
            );
            /*
            virtual bool sendSecurityDefinitionRequest(const SessionID& sessionID,
                                                       const bool manualOrderIndicator,
                                                       const std::string securityReqID,
                                                       const std::string securitySubType,

            );*/


            virtual bool sendQuoteCancel(const SessionID& sessionID,
                                         FIX42::QuoteCancel& quoteCancel);
        private:
            virtual void setCMEHeader(Message&, const SessionID&);
            virtual void setLogon(Message&, const SessionID&);
            virtual void setLogout(Message&, const SessionID&);
            virtual bool isSessionLoggedOn(const SessionID&);
            SessionSettings settings_;
            FileStoreFactory storeFactory_;
            FileLogFactory logFactory_;
            SocketInitiator socketInitiator_;
        };
    } //namespace cme
} //namespace falcon

#endif //FALCON_CMEQFCLIENT_H
