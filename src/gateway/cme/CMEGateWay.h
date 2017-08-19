#ifndef FALCON_CMEGATEWAY_H
#define FALCON_CMEGATEWAY_H

#include <vector>

#include "GateWay.h"

namespace falcon {
    namespace ma{
        class OrderRequest;
        class ActiveOrderMgr;
    };

    namespace cme{

        class CMEApplication;

        ///CME Gateway implementation which encapsulates a FIX-based Session Manager
        class CMEGateWay : public gw::GateWay {
        public:
            CMEGateWay();
            virtual ~CMEGateWay();

            virtual bool start();
            virtual bool stop();
            virtual int32_t handleOrderRequest(const ma::OrderRequest& request);
            virtual int32_t processOrderUpdate();
            virtual bool registerOrderMgr(ma::ActiveOrderMgr* orderMgr);
            virtual bool unregisterOrderMgr(ma::ActiveOrderMgr* orderMgr);

            virtual bool setCMESessionClient(CMEApplication* cmeSessionClient);

        private:
            CMEApplication* sessionClient_{nullptr};

            std::vector<ma::ActiveOrderMgr*> activeOrderMgrs_;
        };
    }// namespace cme
}// namespace falcon


#endif //FALCON_CMEGATEWAY_H