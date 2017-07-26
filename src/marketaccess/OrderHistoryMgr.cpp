#include "OrderHistoryMgr.h"
#include "OrderHistory.h"

namespace falcon {
    namespace ma {
        OrderHistoryMgr::OrderHistoryMgr() {

        };

        OrderHistoryMgr::~OrderHistoryMgr() {

        };

        std::vector<OrderHistory> OrderHistoryMgr::getOrderHistoryByClientOrderID(std::string id) {
            std::vector<OrderHistory> res;
            return res;
        }
    } //namespace ma
} //namespace falcon