
#ifndef FALCON_MDORDERBOOK_H
#define FALCON_MDORDERBOOK_H

#include <cstdint>
#include <vector>
#include <string>
namespace falcon {
    namespace md{

    enum class BidAsk{
        Bid = 0,
        Ask = 1,
    };
    class MDOrderBook {
    public:
        static const int32_t Depth;

        MDOrderBook(const std::string &symbol);
        virtual ~MDOrderBook();

        virtual double getPrice(BidAsk bidAsk, uint8_t pos) const;
        virtual double getQty(BidAsk bidAsk, uint8_t pos) const;

        virtual void setPrice(BidAsk bidAsk, uint8_t pos, double price);
        virtual void setQty(BidAsk bidAsk, uint8_t pos, double qty);
    private:
        std::string symbol_;
        std::vector<double> bidPrice_;
        std::vector<double> askPrice_;
        std::vector<double> bidQty_;
        std::vector<double> askQty_;
    };
    } //namespace md
} //namespace falcon


#endif //FALCON_MDORDERBOOK_H
