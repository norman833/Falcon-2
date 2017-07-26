#ifndef FALCON_ORDERHISTORYMGR_H
#define FALCON_ORDERHISTORYMGR_H

#include <vector>
#include "DBConnection.h"

namespace falcon {
    namespace ma {
        class OrderHistory;

        class OrderHistoryMgr {
        public:
            OrderHistoryMgr();
            virtual ~OrderHistoryMgr();
            virtual std::vector<OrderHistory> getOrderHistoryByClientOrderID(std::string id);
        private:
            falcon::db::DBConnection dbConnection_;
        };
    } //namespace ma
} //namespace falcon

#endif //FALCON_ORDERHISTORYMGR_H
