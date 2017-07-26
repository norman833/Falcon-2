#ifndef FALCON_ORDER_H
#define FALCON_ORDER_H

#include <string>
namespace falcon {
    namespace ma {
        class Order {
        public:
            Order(){};
            virtual ~Order(){};
        public:
            std::string CLIENT_ORDER_ID_;
            std::string EXCH_ORDER_ID_;
            std::string EXCH_ACCOUNT_ID_;
            std::string INSTRUMENT_ID_;
            std::string EXCHANGE_ID_;
            double ORDER_QUANTITY_;
            double ORDER_PRICE_;
            double DISPLAY_QUANTITY_;
            double MINIMUM_QUANTITY_;
            double STOP_PRICE_;
            std::string STOP_CONDITION_;
            std::string EXPIRATION_TIME_;
            std::string ORDER_SIDE_;
            std::string ORDER_SIDE_DETAIL_;
            std::string ORDER_PRICE_TYPE_;
            std::string ORDER_PRICE_TYPE_QUALIFIER_;
            std::string ORDER_EXPIRY_TYPE_;
        };
    } //namespace ma
} //namespace falcon


#endif //FALCON_ORDER_H
