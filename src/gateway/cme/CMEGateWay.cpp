#include <algorithm>

#include "CMEGateWay.h"
#include "CMEApplication.h"

namespace falcon {
    namespace cme{

        CMEGateWay::CMEGateWay() {

        };

        CMEGateWay::~CMEGateWay() {

        };

        bool CMEGateWay::setCMESessionClient(CMEApplication *cmeSession, std::string targetCompID) {
            if(this->sessionClient_){
                return false;
            }
            else{
                this->sessionClient_ = cmeSession;
                this->targetCompID_ = targetCompID;
                this->sessionClient_->setObserver(this);
                return true;
            }
        }
        bool CMEGateWay::isSessionLoggedOn() {
            if(this->sessionClient_){
                return(this->sessionClient_->isSessionLoggedOn(
                        this->sessionClient_->getSessionIDbyTargetCompID(this->targetCompID_)));
            }
            else {
                return false;
            }
        }
        bool CMEGateWay::start() {
            return this->sessionClient_ && this->sessionClient_->start();
        };

        bool CMEGateWay::stop() {
            return this->sessionClient_ && this->sessionClient_->stop(false);
        };


        bool CMEGateWay::registerOrderMgr(CMEOrderInterface *orderMgr) {
            if (std::find(activeOrderMgrs_.begin(), activeOrderMgrs_.end(), orderMgr) !=  activeOrderMgrs_.end() ) {
                activeOrderMgrs_.push_back(orderMgr);
                return true;
            }
            else {
                return  false;
            }
        };

        bool CMEGateWay::unregisterOrderMgr(CMEOrderInterface *orderMgr) {
            if(std::find(activeOrderMgrs_.begin(), activeOrderMgrs_.end(), orderMgr) !=  activeOrderMgrs_.end()) {
                activeOrderMgrs_.erase(std::remove(activeOrderMgrs_.begin(), activeOrderMgrs_.end(), orderMgr), activeOrderMgrs_.end());
                return true;
            }
            else {
                return false;
            }
        };

        bool CMEGateWay::sendNewOrderSingle(std::string account,
                                            std::string clOrdID,
                                            std::string custOrderHandlingInst,
                                            int32_t orderQty,
                                            char ordType,
                                            double price,
                                            char side,
                                            char timeInForce,
                                            double stopPx,
                                            std::string securityDesc,
                                            int32_t minQty,
                                            std::string securityType,
                                            int32_t customerOrFirm,
                                            int32_t maxShow,
                                            std::string expireDate,
                                            bool manualOrderIndicator,
                                            std::string giveUpFirm,
                                            std::string cmtaGiveupCD,
                                            std::string allocAccount) {
            return(this->sessionClient_->sendNewOrderSingle(
                    this->sessionClient_->getSessionIDbyTargetCompID(this->targetCompID_),
                    account,
                    clOrdID,
                    custOrderHandlingInst,
                    orderQty,
                    ordType,
                    price,
                    side,
                    timeInForce,
                    stopPx,
                    securityDesc,
                    minQty,
                    securityType,
                    customerOrFirm,
                    maxShow,
                    expireDate,
                    manualOrderIndicator,
                    giveUpFirm,
                    cmtaGiveupCD,
                    allocAccount
            ));
        }

        bool CMEGateWay::sendOrderCancelRequest(std::string account,
                                                std::string clOrdID,
                                                std::string orderID,
                                                std::string origClOrdID,
                                                char side,
                                                std::string securityDesc,
                                                std::string securityType,
                                                std::string correlationClOrdID,
                                                bool manualOrderIndicator) {

            return(this->sessionClient_->sendOrderCancelRequest(
                    this->sessionClient_->getSessionIDbyTargetCompID(this->targetCompID_),
                    account,
                    clOrdID,
                    orderID,
                    origClOrdID,
                    side,
                    securityDesc,
                    securityType,
                    correlationClOrdID,
                    manualOrderIndicator));
        }

        bool CMEGateWay::sendOrderCancelReplaceRequest(std::string account,
                                                       std::string clOrdID,
                                                       std::string orderID,
                                                       int32_t orderQty,
                                                       std::string custOrderHandlingInst,
                                                       char ordType,
                                                       std::string origClOrdID,
                                                       double price,
                                                       char side,
                                                       char timeInForce,
                                                       bool manualOrderIndicator,
                                                       double stopPx,
                                                       std::string securityDesc,
                                                       int32_t minQty,
                                                       std::string securityType,
                                                       int32_t customerOrFirm,
                                                       int32_t maxShow,
                                                       std::string expireDate,
                                                       std::string correlationClOrdID,
                                                       char IFMFlag,
                                                       std::string giveUpFirm,
                                                       std::string cmtaGiveupCD,
                                                       std::string allocAccount) {

            return(this->sessionClient_->sendOrderCancelReplaceRequest(
                    this->sessionClient_->getSessionIDbyTargetCompID(this->targetCompID_),
                    account,
                    clOrdID,
                    orderID,
                    orderQty,
                    custOrderHandlingInst,
                    ordType,
                    origClOrdID,
                    price,
                    side,
                    timeInForce,
                    manualOrderIndicator,
                    stopPx,
                    securityDesc,
                    minQty,
                    securityType,
                    customerOrFirm,
                    maxShow,
                    expireDate,
                    correlationClOrdID,
                    IFMFlag,
                    giveUpFirm,
                    cmtaGiveupCD,
                    allocAccount
            ));
        }

        bool CMEGateWay::sendOrderStatusRequest(std::string clOrdID,
                                                std::string orderID,
                                                char side,
                                                std::string securityDesc,
                                                std::string securityType,
                                                std::string correlationClOrdID,
                                                bool manualOrderIndicator) {
            return(this->sessionClient_->sendOrderStatusRequest(
                    this->sessionClient_->getSessionIDbyTargetCompID(this->targetCompID_),
                    clOrdID,
                    orderID,
                    side,
                    securityDesc,
                    securityType,
                    correlationClOrdID,
                    manualOrderIndicator
            ));
        }

        bool CMEGateWay::sendOrderMassActionRequest(std::string clOrdID,
                                                    int32_t massActionScope,
                                                    int32_t marketSegmentID,
                                                    std::string symbol,
                                                    std::string securityDesc,
                                                    int32_t massCancelRequestType,
                                                    std::string account,
                                                    char side,
                                                    char ordType,
                                                    char timeInForce,
                                                    bool manualOrderIndicator) {
            return(this->sessionClient_->sendOrderMassActionRequest(
                    this->sessionClient_->getSessionIDbyTargetCompID(this->targetCompID_),
                    clOrdID,
                    massActionScope,
                    marketSegmentID,
                    symbol,
                    securityDesc,
                    massCancelRequestType,
                    account,
                    side,
                    ordType,
                    timeInForce,
                    manualOrderIndicator
            ));
        }

        void CMEGateWay::onMessage(const FIX42::Reject &reject) {
            for( CMEOrderInterface* orderMgr: this->activeOrderMgrs_){
                orderMgr->onMessage(reject);
            }
        };

        void CMEGateWay::onMessage(const FIX42::ExecutionReport &executionReport) {
            for( CMEOrderInterface* orderMgr: this->activeOrderMgrs_){
                orderMgr->onMessage(executionReport);
            }
        }

        void CMEGateWay::onMessage(const FIX42::OrderCancelReject &orderCancelReject) {
            for( CMEOrderInterface* orderMgr: this->activeOrderMgrs_){
                orderMgr->onMessage(orderCancelReject);
            }
        }

        void CMEGateWay::onMessage(const FIX42::BusinessMessageReject &businessMessageReject) {
            for (CMEOrderInterface *orderMgr: this->activeOrderMgrs_) {
                orderMgr->onMessage(businessMessageReject);
            }
        }

        void CMEGateWay::onMessage(const FIX50SP2::OrderMassActionReport &orderMassActionReport) {
            for( CMEOrderInterface* orderMgr: this->activeOrderMgrs_){
                orderMgr->onMessage(orderMassActionReport);
            }
        }
    }// namespace cme
}// namespace falcon