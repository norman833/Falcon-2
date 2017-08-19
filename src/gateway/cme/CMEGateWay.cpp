#include <algorithm>

#include "CMEGateWay.h"
#include "CMEApplication.h"
#include "../../marketaccess/OrderRequest.h"
#include "../../marketaccess/ActiveOrderMgr.h"

namespace falcon {
    namespace cme{

        CMEGateWay::CMEGateWay() {

        };

        CMEGateWay::~CMEGateWay() {

        };

        bool CMEGateWay::setCMESessionClient(CMEApplication *cmeSession) {
            if(this->sessionClient_){
                return false;
            }
            else{
                this->sessionClient_ = cmeSession;
                return true;
            }
        }

        bool CMEGateWay::start() {
            return this->sessionClient_ && this->sessionClient_->start();
        };

        bool CMEGateWay::stop() {
            return this->sessionClient_ && this->sessionClient_->stop(false);
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