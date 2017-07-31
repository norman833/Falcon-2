#ifndef FALCON_ORDERREQUESTMGR_H
#define FALCON_ORDERREQUESTMGR_H

#include <vector>
#include <string>
#include <unordered_map>
#include "DBConnection.h"
#include "GateWay.h"

namespace falcon {
    namespace ma {
        class OrderRequest;

        class OrderRequestMgr {
        public:
            OrderRequestMgr();
            virtual ~OrderRequestMgr();

            virtual bool start();
            virtual bool stop();
            virtual bool isStarted() const;
            virtual bool addGateWay(const std::string name, const falcon::gw::GateWay* gateway);
            virtual bool removeGateWay(const std::string gateway);

        private:
            virtual  std::vector<OrderRequest> getOrderRequests();
            virtual  int32_t validateOrderRequest(const OrderRequest& request) const;
            virtual  bool processOrderRequests(const OrderRequest& request);

        private:
            bool started_;
            falcon::db::DBConnection* dbConnection_;
            std::unordered_map<std::string, falcon::gw::GateWay*> gateWayMap_;
        };
    } //namespace ma
} //namespace falcon


#endif //FALCON_ORDERREQUESTMGR_H
