#ifndef FALCON_GATEWAY_H
#define FALCON_GATEWAY_H

#include <cstdint>
namespace falcon {
    namespace ma{
        class OrderRequest;
        class ActiveOrderMgr;
    };

    namespace gw {

        class OrderRequest;
        class ActiveOrderMgr;

        /// A virtual base class for Gateway. Specific exchange gateways should inherit this class
        class GateWay {
        public:
            virtual int32_t start() = 0;
            virtual int32_t stop() = 0;
            virtual int32_t handleOrderRequest(const ma::OrderRequest& request) = 0;
            virtual int32_t processOrderUpdate() = 0;
            virtual bool registerOrderMgr(const ma::ActiveOrderMgr* orderMgr) = 0;
            virtual bool unregisterOrderMgr(const ma::ActiveOrderMgr* orderMgr) = 0;
        };
    }// namespace gw
}// namespace falcon

#endif //FALCON_GATEWAY_H
