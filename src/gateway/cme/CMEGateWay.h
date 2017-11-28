#ifndef FALCON_CMEGATEWAY_H
#define FALCON_CMEGATEWAY_H

#include <vector>
#include <string>

#include "CMEOrderInterface.h"

namespace falcon {
    namespace cme{

        class CMEApplication;

        ///CME Gateway implementation which encapsulates a FIX-based Session Manager
        class CMEGateWay: public CMEOrderInterface {
        public:
            CMEGateWay();
            virtual ~CMEGateWay();

            virtual bool start();
            virtual bool stop();

            virtual bool registerOrderMgr(CMEOrderInterface* orderMgr);
            virtual bool unregisterOrderMgr(CMEOrderInterface* orderMgr);
            virtual bool setCMESessionClient(CMEApplication* cmeSessionClient, std::string targetCompID);
            virtual bool isSessionLoggedOn();
            virtual bool sendOrderCancelRequest(std::string account,
                                                std::string clOrdID,
                                                std::string orderID,
                                                std::string origClOrdID,
                                                char side,
                                                std::string securityDesc,
                                                std::string securityType,
                                                std::string correlationClOrdID,
                                                bool manualOrderIndicator
            );
            virtual bool sendOrderCancelReplaceRequest(std::string account,
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
            virtual bool sendNewOrderSingle(std::string account,
                                            std::string clOrdID,
                                            std::string custOrderHandlingInst,
                                            int32_t orderQty,
                                            char ordType,
                                            double price,
                                            char side,
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
            virtual bool sendOrderStatusRequest(std::string clOrdID,
                                                std::string orderID,
                                                char side,
                                                std::string securityDesc,
                                                std::string securityType,
                                                std::string correlationClOrdID,
                                                bool manualOrderIndicator
            );

            virtual void onMessage(const FIX42::BusinessMessageReject& businessMessageReject);
            virtual void onMessage(const FIX42::Reject& reject);

            virtual void onMessage(const FIX42::ExecutionReport& executionReport);
            virtual void onMessage(const FIX42::OrderCancelReject& orderCancelReject);
        private:
            CMEApplication* sessionClient_{nullptr};
            std::string targetCompID_;
            std::vector<CMEOrderInterface*> activeOrderMgrs_;
        };
    }// namespace cme
}// namespace falcon


#endif //FALCON_CMEGATEWAY_H
