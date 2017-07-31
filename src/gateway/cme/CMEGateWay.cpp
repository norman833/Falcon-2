#include "CMEGateWay.h"

namespace falcon {
    namespace cme{
        int32_t CMEGateWay::start() {
            return 0;
        };

        int32_t CMEGateWay::stop() {
            return 0;
        };

        int32_t CMEGateWay::handleOrderRequest(const OrderRequest &request) {
            return 0;
        };

        int32_t CMEGateWay::processOrderUpdate() {
            return  0;
        };

        bool CMEGateWay::registerOrderMgr(const ActiveOrderMgr *orderMgr) {
            return  true;
        };

        bool CMEGateWay::unregisterOrderMgr(const ActiveOrderMgr *orderMgr) {
            return  true;
        };

    }// namespace cme
}// namespace falcon