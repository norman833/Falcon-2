#ifndef CMEORDERINTERFACE_H
#define CMEORDERINTERFACE_H

#include "quickfix/Message.h"
#include "quickfix/MessageCracker.h"

namespace falcon {
    namespace cme {
        class CMEOrderInterface{
        public:
            virtual void onMessage(const FIX42::BusinessMessageReject& businessMessageReject) = 0;
            virtual void onMessage(const FIX42::Reject& reject) = 0;

            virtual void onMessage(const FIX42::ExecutionReport& executionReport) = 0;
            virtual void onMessage(const FIX42::OrderCancelReject& orderCancelReject) = 0;
            virtual void onMessage(const FIX50SP2::OrderMassActionReport& orderMassActionReport) = 0;
        };
    }// namespace cme
}// namespace falcon

#endif //CMEORDERINTERFACE_H
