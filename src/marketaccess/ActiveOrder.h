#ifndef FALCON_ACTIVEORDER_H
#define FALCON_ACTIVEORDER_H

#include <string>
#include <cstdint>
#include "Order.h"

namespace falcon {
    namespace ma {
        class ActiveOrder : public Order {
        public:
            ActiveOrder(){};
            virtual ~ActiveOrder(){};

        public:
            double FILL_QUANTITY_;
            double AVERAGE_PRICE_;
            std::string ORDER_STATUS_;
            std::string UPDATE_TIME_;
            uint32_t ORDER_VERSION_;
        };
    } //namespace ma
} //namespace falcon
#endif //FALCON_ACTIVEORDER_H
