#ifndef FALCON_ORDERREQUEST_H
#define FALCON_ORDERREQUEST_H

#include <cstdint>
#include <string>
#include "Order.h"

namespace falcon {
    namespace ma {
        class OrderRequest : public Order {
        public:
            OrderRequest(){};
            virtual ~OrderRequest(){};

        public:
            std::string REQUEST_ID_;
            std::string LAST_REQUEST_ID;
            std::string ORIGINAL_REQUEST_ID_;
            std::string REQUEST_TIME_;
            std::string REQUEST_TYPE_;
        };
    } //namespace ma
} //namespace falcon

#endif //FALCON_ORDERREQUEST_H
