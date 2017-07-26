#include "OrderRequestMgr.h"
#include "OrderRequest.h"

namespace falcon {
    namespace ma {
        OrderRequestMgr::OrderRequestMgr() {

        };

        OrderRequestMgr::~OrderRequestMgr() {

        };

        bool OrderRequestMgr::start() {

            return true;
        }

        bool OrderRequestMgr::stop() {

            return true;
        }

        bool OrderRequestMgr::isStarted() const {
            return this->started_;
        }

        bool OrderRequestMgr::addGateWay(const std::string name, const falcon::gw::GateWay* gateway) {
            return true;
        }

        bool OrderRequestMgr::removeGateWay(const std::string gateway) {

            return true;
        }

        std::vector<OrderRequest> OrderRequestMgr::getOrderRequests(){
            std::vector<OrderRequest> res;
            return res;
        };

        int32_t OrderRequestMgr::validateOrderRequest(const OrderRequest& request) const{
            return 0;
        };

        bool OrderRequestMgr::processOrderRequests(const OrderRequest& request){
            return true;
        }
    } //namespace ma
} //namespace falcon
