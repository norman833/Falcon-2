#ifndef FALCON_ORDERHISTORY_H
#define FALCON_ORDERHISTORY_H

#include "Order.h"
namespace falcon {
    namespace ma {

        class OrderHistory : public Order {
        public:
            OrderHistory(){};
            virtual ~OrderHistory(){};
        public:
            std::string REQUEST_ID_;
            std::string REQUEST_TIME_;
            std::string REQUEST_TYPE_;

            uint32_t ORDER_VERSION_;
            std::string ORDER_STATUS_;
            std::string ORDER_STATUS_DESC_;
            double FILL_QUANTITY_;
            std::string UPDATE_TIME_;
        };
    } //namespace ma
} //namespace falcon


#endif //FALCON_ORDERHISTORY_H
