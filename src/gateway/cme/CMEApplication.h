#ifndef FALCON_CMEQFCLIENT_H
#define FALCON_CMEQFCLIENT_H

#include <cstdint>
#include <mutex>

#include "CMEOrderInterface.h"

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

        struct LegFuture{
            std::string legSymbol_;
            std::string legSecurityDesc_;
            char legSide_;
            double legPrice_;
            double legOptionRatio_;
        };

        struct LegOption{
            std::string legSymbol_;
            std::string legSecurityDesc_;
            char legSide_;
            int32_t legRatioQty_;
        };

        struct QuoteCancelEntry{
            std::string symbol_;
            std::string securityDesc_;
            std::string quoteSetID_;
            int32_t bidSize_;
            int32_t offerSize_;
        };

        struct QuoteEntry{
            std::string quoteEntryID_;
            std::string symbol_;
            std::string securityDesc_;
            std::string securityType_;
            int32_t securityID_;
            char SecurityIDSource_ = '8';
            double bidPx_;
            int32_t bidSize_;
            double offerPx_;
            int32_t offerSize_;
        };

        struct QuoteSet{
            std::string quoteSetID_;
            std::string underlyingSecurityDesc_;
            int32_t NoQuoteEntries_;//same as TotQuoteEntries
            std::vector<QuoteEntry> quoteEntries_;
        };

        struct CrossEntry{
            char side_;
            std::string account_;
            std::string clOrdID_;
            std::string custOrderHandlingInst_;
            int32_t orderQty_;
            char sideTimeInForce_;
            int32_t customerOrFirm_;
        };

        class CMEApplication : public Application, MessageCracker {
        public:
            explicit CMEApplication(std::string settingFile);
            virtual ~CMEApplication();
            virtual bool start();
            virtual bool stop(bool force);
            virtual SessionID getSessionIDbyTargetCompID(std::string targetCompID);
            virtual bool isSessionLoggedOn(const SessionID&);
            virtual bool setObserver(CMEOrderInterface* observer);

            virtual void onCreate( const SessionID& sessionID);
            virtual void onLogon( const SessionID& sessionID);
            virtual void onLogout( const SessionID& sessionID);
            virtual void toAdmin( Message& message, const SessionID& sessionID);
            virtual void toApp( Message& message, const SessionID& sessionID) throw( DoNotSend );
            virtual void fromAdmin( const Message& message, const SessionID& sessionID)
                throw( FieldNotFound, IncorrectDataFormat, IncorrectTagValue, RejectLogon );
            virtual void fromApp( const Message&message, const SessionID& sessionID)
                throw( FieldNotFound, IncorrectDataFormat, IncorrectTagValue, UnsupportedMessageType );

            virtual void onMessage(const FIX42::TestRequest& testRequest, const SessionID& sessionID);

            virtual void onMessage(const FIX42::Reject& reject, const SessionID& sessionID);
            virtual void onMessage(const FIX42::BusinessMessageReject& businessMessageReject, const SessionID& sessionID);
            virtual void onMessage(const FIX42::ExecutionReport& executionReport, const SessionID& sessionID);
            virtual void onMessage(const FIX42::OrderCancelReject& orderCancelReject, const SessionID& sessionID);
            virtual void onMessage(const FIX50SP2::OrderMassActionReport& orderMassActionReport);

            //virtual void onMessage(const FIX42::QuoteAcknowledgement& quoteAcknowledgement, const SessionID& sessionID);

            virtual bool sendTestRequest(const SessionID& sessionID, std::string msg);
            virtual bool sendOrderCancelRequest(const SessionID& sessionID,
                                                std::string account,
                                                std::string clOrdID,
                                                std::string orderID,
                                                std::string origClOrdID,
                                                char side,
                                                std::string securityDesc,
                                                std::string securityType,
                                                std::string correlationClOrdID,
                                                bool manualOrderIndicator
            );
            virtual bool sendOrderCancelReplaceRequest(const SessionID& sessionID,
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
                                                       std::string allocAccount
            );
            virtual bool sendNewOrderSingle(const SessionID& sessionID,
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
                                            std::string allocAccount
            );
            virtual bool sendOrderStatusRequest(const SessionID& sessionID,
                                                std::string clOrdID,
                                                std::string orderID,
                                                char side,
                                                std::string securityDesc,
                                                std::string securityType,
                                                std::string correlationClOrdID,
                                                bool manualOrderIndicator
            );

            virtual bool sendOrderMassStatusReport(const SessionID& sessionID,
                                                   std::string massStatusReqID,
                                                   int32_t massStatusReqType,
                                                   int32_t marketSegmentID,
                                                   int32_t ordStatusReqType,
                                                   std::string account,
                                                   std::string symbol,
                                                   std::string securityDesc,
                                                   char timeInForce,
                                                   bool manualOrderIndicator
            );

            virtual bool sendQuoteRequest(const SessionID& sessionID,
                                          std::string quoteReqID,
                                          std::string symbol,
                                          int32_t orderQty,
                                          char side,
                                          std::string securityDesc,
                                          std::string securityType,
                                          std::string custOrderHandlingInst,
                                          bool manualOrderIndicator
            );

            virtual bool sendSecurityDefinitionRequest(const SessionID& sessionID,
                                                       bool manualOrderIndicator,
                                                       std::string securityReqID,
                                                       std::string securitySubType,
                                                       int32_t noLegs,
                                                       int32_t legOptionSize,
                                                       std::vector<LegOption> legOption,
                                                       int32_t legFutureSize,
                                                       std::vector<LegFuture> legFuture
            );

            virtual bool sendOrderMassActionRequest(const SessionID& sessionID,
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
                                                    bool manualOrderIndicator
            );

            virtual bool sendMassQuote(const SessionID& sessionID,
                                       std::string quoteReqID,
                                       std::string quoteID,
                                       std::string MMAccount,
                                       bool manualOrderIndicator,
                                       std::string custOrderHandlingInst,
                                       int32_t customerOrFirm,
                                       int32_t NoQuoteSets,
                                       const std::vector<QuoteSet>& quoteSet
            );

            virtual bool sendQuoteCancel(const SessionID& sessionID,
                                         std::string quoteID,
                                         int32_t quoteCancelType,
                                         bool manualOrderIndicator,
                                         int32_t noQuoteEntries,
                                         const std::vector<QuoteCancelEntry>& quoteCancelEntries
            );

            virtual bool sendNewOrderCross(const SessionID& sessionID,
                                           double price,
                                           std::string symbol,
                                           bool manualOrderIndicator,
                                           std::string securityDesc,
                                           std::string securityType,
                                           std::string crossID,
                                           const std::vector<CrossEntry>& crossEntries
            );
        private:
            virtual void setCMEHeader(Message&, const SessionID&);
            virtual void setLogon(Message&, const SessionID&);
            virtual void setLogout(Message&, const SessionID&);

            SessionSettings settings_;
            FileStoreFactory storeFactory_;
            FileLogFactory logFactory_;
            SocketInitiator socketInitiator_;

            long latestSeqNo = 0;
            std::mutex latestSeqNO_mutex;

            CMEOrderInterface* observer_{nullptr};
        };
    } //namespace cme
} //namespace falcon

#endif //FALCON_CMEQFCLIENT_H
