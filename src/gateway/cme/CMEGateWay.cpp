#include <algorithm>

#include "CMEGateWay.h"
#include "CMESessionClient.h"
#include "../../marketaccess/OrderRequest.h"
#include "../../marketaccess/ActiveOrderMgr.h"

namespace falcon {
    namespace cme{

        CMEGateWay::CMEGateWay() {

        };

        CMEGateWay::~CMEGateWay() {

        };

        bool CMEGateWay::setCMESessionClient(ReliableCMESessionClient *reliableCMESessionClient) {
            if(this->sessionClient_){
                return false;
            }
            else{
                this->sessionClient_ = reliableCMESessionClient;
                return true;
            }
        }

        int32_t CMEGateWay::start() {

            this->sessionClient_->start(false);
            return 0;
        };

        int32_t CMEGateWay::stop() {

            this->sessionClient_->session_ptr()->stop();
            return 0;
        };

        int32_t CMEGateWay::handleOrderRequest(const ma::OrderRequest &request) {
            return 0;
        };

        int32_t CMEGateWay::processOrderUpdate() {
            return  0;
        };

        bool CMEGateWay::registerOrderMgr(ma::ActiveOrderMgr *orderMgr) {
            if (std::find(activeOrderMgrs_.begin(), activeOrderMgrs_.end(), orderMgr) !=  activeOrderMgrs_.end() ) {
                activeOrderMgrs_.push_back(orderMgr);
                return true;
            }
            else {
                return  false;
            }
        };

        bool CMEGateWay::unregisterOrderMgr(ma::ActiveOrderMgr *orderMgr) {
            if(std::find(activeOrderMgrs_.begin(), activeOrderMgrs_.end(), orderMgr) !=  activeOrderMgrs_.end()) {
                activeOrderMgrs_.erase(std::remove(activeOrderMgrs_.begin(), activeOrderMgrs_.end(), orderMgr), activeOrderMgrs_.end());
                return true;
            }
            else {
                return false;
            }
        };

    }// namespace cme
}// namespace falcon