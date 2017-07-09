
#include "MDOrderBook.h"
namespace falcon {
    namespace md{
        const int32_t MDOrderBook::Depth = 10;

        MDOrderBook::MDOrderBook(const std::string &symbol) : symbol_(symbol){
            for(int i = 0; i < MDOrderBook::Depth; ++i) {
                this->askPrice_[i] = this->bidPrice_[i] = this->askQty_[i] = this->bidQty_[i] = 0;
            }
        };

        MDOrderBook::~MDOrderBook() {
        };

        double MDOrderBook::getPrice(BidAsk bidAsk, uint8_t pos) const {
            if(bidAsk == BidAsk::Bid)
                return(this->bidPrice_[pos]);
            else
                return(this->askPrice_[pos]);
        };

        double MDOrderBook::getQty(BidAsk bidAsk, uint8_t pos) const {
            if(bidAsk == BidAsk::Bid)
                return(this->bidQty_[pos]);
            else
                return(this->askQty_[pos]);
        }

        void MDOrderBook::setPrice(BidAsk bidAsk, uint8_t pos, double price) {
            if(bidAsk == BidAsk::Bid)
                this->bidPrice_[pos] = price;
            else
                this->askPrice_[pos] = price;
        }

        void MDOrderBook::setQty(BidAsk bidAsk, uint8_t pos, double qty) {
            if(bidAsk == BidAsk::Bid)
                this->bidQty_[pos] = qty;
            else
                this->askQty_[pos] = qty;
        }

    } //namespace md
} //namespace falcon
