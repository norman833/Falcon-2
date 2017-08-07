#ifndef FALCON_CMEMSGROUTER_H
#define FALCON_CMEMSGROUTER_H

#include "CMEFIX_router.hpp"
namespace falcon {
    namespace cme {
        class CMESessionClientBase;

        class CMEMsgRouter : public FIX8::CMEFIX::CMEFIX_Router {
        public:
            virtual bool operator() (const class Message *msg) const{ return false; };
            virtual bool operator() (const class Heartbeat *msg) const;
            virtual bool operator() (const class TestRequest *msg) const{ return false; };
            virtual bool operator() (const class ResendRequest *msg) const{ return  false; };
            virtual bool operator() (const class Reject *msg) const;
            virtual bool operator() (const class SequenceReset *msg) const;
            virtual bool operator() (const class Logout *msg) const;
            virtual bool operator() (const class IndicationofInterest *msg) const{ return false; };
            virtual bool operator() (const class Advertisement *msg) const {return false; };
            virtual bool operator() (const class ExecutionReport *msg) const;
            virtual bool operator() (const class OrderCancelReject *msg) const;
            virtual bool operator() (const class Logon *msg) const;
            virtual bool operator() (const class News *msg) const {return false; };
            virtual bool operator() (const class Email *msg) const {return false; };
            virtual bool operator() (const class NewOrderSingle *msg) const;
            virtual bool operator() (const class NewOrderList *msg) const;
            virtual bool operator() (const class OrderCancelRequest *msg) const;
            virtual bool operator() (const class OrderCancelReplaceRequest *msg) const;
            virtual bool operator() (const class OrderStatusRequest *msg) const { return false; }
            virtual bool operator() (const class Allocation *msg) const { return false; }
            virtual bool operator() (const class ListCancelRequest *msg) const { return false; }
            virtual bool operator() (const class ListExecute *msg) const { return false; }
            virtual bool operator() (const class ListStatusRequest *msg) const { return false; }
            virtual bool operator() (const class ListStatus *msg) const { return false; }
            virtual bool operator() (const class AllocationACK *msg) const { return false; }
            virtual bool operator() (const class DontKnowTrade *msg) const { return false; }
            virtual bool operator() (const class QuoteRequest *msg) const { return false; }
            virtual bool operator() (const class Quote *msg) const { return false; }
            virtual bool operator() (const class SettlementInstructions *msg) const { return false; }
            virtual bool operator() (const class MarketDataRequest *msg) const { return false; }
            virtual bool operator() (const class MarketDataSnapshotFullRefresh *msg) const { return false; }
            virtual bool operator() (const class MarketDataIncrementalRefresh *msg) const { return false; }
            virtual bool operator() (const class MarketDataRequestReject *msg) const { return false; }
            virtual bool operator() (const class QuoteCancel *msg) const { return false; }
            virtual bool operator() (const class QuoteStatusRequest *msg) const { return false; }
            virtual bool operator() (const class QuoteAcknowledgement *msg) const { return false; }
            virtual bool operator() (const class SecurityDefinitionRequest *msg) const { return false; }
            virtual bool operator() (const class SecurityDefinition *msg) const { return false; }
            virtual bool operator() (const class SecurityStatusRequest *msg) const { return false; }
            virtual bool operator() (const class SecurityStatus *msg) const { return false; }
            virtual bool operator() (const class TradingSessionStatusRequest *msg) const { return false; }
            virtual bool operator() (const class TradingSessionStatus *msg) const { return false; }
            virtual bool operator() (const class MassQuote *msg) const { return false; }
            virtual bool operator() (const class BusinessMessageReject *msg) const { return false; }
            virtual bool operator() (const class BidRequest *msg) const { return false; }
            virtual bool operator() (const class BidResponse *msg) const { return false; }
            virtual bool operator() (const class ListStrikePrice *msg) const { return false; }
        private:
            CMESessionClientBase*  cmeSessionClientBase_;
        };
} //namespace cme
} //namespace falcon

#endif //FALCON_CMEMSGROUTER_H
