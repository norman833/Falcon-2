#ifndef FALCON_ACTIVEORDERMGR_H
#define FALCON_ACTIVEORDERMGR_H

#include <string>
#include <vector>
#include "DBConnection.h"
#include "GateWay.h"

namespace falcon {
    namespace ma {

        class ActiveOrder;

        class ActiveOrderMgr {
        public:
            ActiveOrderMgr();
            virtual ~ActiveOrderMgr();

            virtual ActiveOrder getActiveOrderbyClientOrderID(const std::string id);
            virtual ActiveOrder getActiveOrderbyExchangeOrderID(const std::string id);
            virtual std::vector<ActiveOrder> getActiveOrderbyExchange(const std::string exchange);

            virtual bool processOrderUpdate();

        private:
            falcon::db::DBConnection* dbConnection_;
        };
    } //namespace ma
} //namespace falcon

#endif //FALCON_ACTIVEORDERMGR_H
