#ifndef FALCON_CMEGATEWAY_H
#define FALCON_CMEGATEWAY_H

#include "GateWay.h"

namespace falcon {
    namespace cme{

        class OrderRequest;
        class ActiveOrderMgr;

        ///CME Gateway implementation which encapsulates a FIX-based Session Manager
        class CMEGateWay : public gw::GateWay {
        public:
            CMEGateWay();
            virtual ~CMEGateWay();

            virtual int32_t start();
            virtual int32_t stop();
            virtual int32_t handleOrderRequest(const OrderRequest& request);
            virtual int32_t processOrderUpdate();
            virtual bool registerOrderMgr(const ActiveOrderMgr* orderMgr);
            virtual bool unregisterOrderMgr(const ActiveOrderMgr* orderMgr);

        private:

        };
    }// namespace cme
}// namespace falcon


#endif //FALCON_CMEGATEWAY_H
