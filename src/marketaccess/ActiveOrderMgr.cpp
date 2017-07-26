#include "ActiveOrderMgr.h"
#include "ActiveOrder.h"

namespace falcon {
    namespace ma {
        ActiveOrderMgr::ActiveOrderMgr() {

        };

        ActiveOrderMgr::~ActiveOrderMgr() {

        };

        ActiveOrder ActiveOrderMgr::getActiveOrderbyClientOrderID(const std::string id) {
            ActiveOrder order;

            return order;
        };

        ActiveOrder ActiveOrderMgr::getActiveOrderbyExchangeOrderID(const std::string id) {
            ActiveOrder order;
            return order;
        };

        std::vector<ActiveOrder> ActiveOrderMgr::getActiveOrderbyExchange(const std::string exchange) {
            std::vector<ActiveOrder> res;

            return res;
        }

    } //namespace ma
} //namespace falcon
