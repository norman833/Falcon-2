#include <string>
#include <ctime>
#include <sstream>

#include "CMEGateWay.h"
#include "CMEApplication.h"
#include "Logger.h"

using namespace std;
using namespace falcon;
using namespace falcon::cme;

void sendTestRequest(CMEApplication& cmeApplication){
    auto sessionID = cmeApplication.getSessionIDbyTargetCompID("CME");
    std::cout << "Session ID is " << sessionID.toString() << std::endl;
    cmeApplication.sendTestRequest(sessionID, "Test01");
    std::cout << "Test Request sent" << std::endl;
}

void cancelOrder(CMEApplication& cmeApplication){
    std::string account;
    std::string clOrdID;
    std::string orderID;
    std::string origClOrdID;
    char side;
    std::string securityDesc;
    std::string securityType;
    std::string correlationClOrdID;
    bool manualOrderIndicator;

    std::cout << "Input Account(string)" << std::endl;
    std::cin >> account;
    std::cout << "Input ClOrdID(string)" << std::endl;
    std::cin >> clOrdID;
    std::cout << "Input OrderID(string)" << std::endl;
    std::cin >> orderID;
    std::cout << "Input OrigClOrdID(string)" << std::endl;
    std::cin >> origClOrdID;
    std::cout << "Input Side(char)" << std::endl;
    std::cin >> side;
    std::cout << "Input SecurityDesc(string)" << std::endl;
    std::cin.ignore(1024, '\n');
    std::getline(std::cin, securityDesc);
    std::cout << "Input SecurityType(string)" << std::endl;
    std::cin >> securityType;
    std::cout << "Input CorrelationClOrdID(string)" << std::endl;
    std::cin >> correlationClOrdID;
    std::cout << "Input ManualOrderIndicator(bool)" << std::endl;
    std::cin >> manualOrderIndicator;

    std::cout << "Confirm? (Y/N):";
    char yesNo;
    std::cin >>yesNo;
    if(yesNo != 'Y')
        return;

    auto res = cmeApplication.sendOrderCancelRequest(cmeApplication.getSessionIDbyTargetCompID("CME"),
                                                account,
                                                clOrdID,
                                                orderID,
                                                origClOrdID,
                                                side,
                                                securityDesc,
                                                securityType,
                                                correlationClOrdID,
                                                manualOrderIndicator);
    if(res)
        std::cout << "order " << clOrdID << " sent" << std::endl;
    else
        std::cout << "order " << clOrdID << " not sent" << std::endl;
}

void placeNewOrder(CMEApplication& cmeApplication){
    std::string account;
    std::string clOrdID;
    std::string custOrderHandlingInst;
    int32_t orderQty;
    char ordType;
    double price;
    char side;
    char timeInForce;
    double stopPx;
    std::string securityDesc;
    int32_t minQty;
    std::string securityType;
    int32_t customerOrFirm;
    int32_t maxShow;
    std::string expireDate;
    bool manualOrderIndicator;
    std::string giveUpFirm;
    std::string cmtaGiveupCD;
    std::string allocAccount;

    std::cout << "Input Account(string)" << std::endl;
    std::cin >> account;
    std::cout << "Input ClOrdID(string)" << std::endl;
    std::cin >> clOrdID;
    std::cout << "Input custOrderHandlingInst(string)" << std::endl;
    std::cin >> custOrderHandlingInst;
    std::cout << "Input OrderQty(int)" << std::endl;
    std::cin >> orderQty;
    std::cout << "Input OrdType(char  1=Market 2=Limit 3=Stop 4=Stop-limit K=Market-Limit)" << std::endl;
    std::cin >> ordType;
    std::cout << "Input Price(double, used in limit orders only)" << std::endl;
    std::cin >> price;
    std::cout << "Input Side(char 1=buy 2=sell)" << std::endl;
    std::cin >> side;
    std::cout << "Input TimeInForce(char 0=Day 1=GTC 3=FAK 6=GTD)" << std::endl;
    std::cin >> timeInForce;
    std::cout << "Input StopPx(double/0 if N/A)" << std::endl;
    std::cin >> stopPx;
    std::cout << "Input SecurityDesc(string)" << std::endl;
    std::cin.ignore(1024,'\n');
    std::getline(std::cin, securityDesc);
    std::cout << "Input MinQty(int/0 if N/A)" << std::endl;
    std::cin >> minQty;
    std::cout << "Input SecurityType(string)" << std::endl;
    std::cin >> securityType;
    std::cout <<"Input CustomerOrFirm(int/0/1)" << std::endl;
    std::cin >> customerOrFirm;
    std::cout << "Input MaxShow(int/OrdQty if N/A)" << std::endl;
    std::cin >> maxShow;
    std::cout << "Input ExpireDate(string/YYYYMMDD, used in GTD only)" << std::endl;
    std::cin >> expireDate;
    std::cout << "Input ManualOrderIndicator(bool)" << std::endl;
    std::cin >> manualOrderIndicator;
    std::cout <<"Input GiveUpFirm(str(3), NA if N/A)" << std::endl;
    std::cin >> giveUpFirm;
    std::cout << "Input CmtaGiveupCD(GU/SX(NA if N/A))" << std::endl;
    std::cin >> cmtaGiveupCD;
    std::cout << "Input allocAccount(str(11), NA if N/A)" << std::endl;
    std::cin >> allocAccount;

    std::cout << "Confirm? (Y/N):";
    char yesNo;
    std::cin >>yesNo;
    if(yesNo != 'Y')
        return;

   auto res = cmeApplication.sendNewOrderSingle(cmeApplication.getSessionIDbyTargetCompID("CME"),
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
    );

    if(res)
        std::cout << "order " << clOrdID << " sent" << std::endl;
    else
        std::cout << "order " << clOrdID << " not sent" << std::endl;
}

void sendMultipleOrders(CMEApplication& cmeApplication){

    int32_t num;
    unsigned interval;
    std::string securityDesc;
    std::cout << "Input number of orders" << std::endl;
    std::cin >> num;
    std::cout << "Input interval of orders" << std::endl;
    std::cin >> interval;
    std::cout << "Input SecurityDesc(string)" << std::endl;
    std::cin >> securityDesc;

    for( auto i = 0; i < interval; ++i){
        int32_t  qty = 100 + i;
        double price = qty;
        std::string clOrdID = "20180104B" + std::to_string(i);
        auto res = cmeApplication.sendNewOrderSingle(cmeApplication.getSessionIDbyTargetCompID("CME"),
                                                     "ABC",
                                                     clOrdID,
                                                     "F",
                                                     qty,
                                                     '2', //orderType
                                                     price, //price
                                                     '0', //side
                                                     '0', //timeInForce
                                                     0, //stopPx
                                                     securityDesc,
                                                     0,
                                                     "FUT",
                                                     0,
                                                     qty,
                                                     "",//expireDate
                                                     1,
                                                     "NA",
                                                     "NA",
                                                     "NA"
        );

        if(res)
            std::cout << "order " << clOrdID << " sent" << std::endl;
        else
            std::cout << "order " << clOrdID << " not sent" << std::endl;

        sleep(interval);
    }
}

void amendOrder(CMEApplication& cmeApplication) {
    std::string account;
    std::string clOrdID;
    std::string orderID;
    int32_t orderQty;
    std::string custOrderHandlingInst;
    char ordType;
    std::string origClOrdID;
    double price;
    char side;
    char timeInForce;
    bool manualOrderIndicator;
    double stopPx;
    std::string securityDesc;
    int32_t minQty;
    std::string securityType;
    int32_t customerOrFirm;
    int32_t maxShow;
    std::string expireDate;
    std::string correlationClOrdID;
    char IFMFlag = 'N';
    std::string giveUpFirm;
    std::string cmtaGiveupCD;
    std::string allocAccount;

    std::cout << "Input Account(string)" << std::endl;
    std::cin >> account;
    std::cout << "Input ClOrdID(string)" << std::endl;
    std::cin >> clOrdID;
    std::cout << "Input OrderID(string)" << std::endl;
    std::cin >> orderID;
    std::cout << "Input OrigClOrdID(string)" << std::endl;
    std::cin >> origClOrdID;
    std::cout << "Input CorrelationClOrdID(string)" << std::endl;
    std::cin >> correlationClOrdID;

    std::cout << "Input custOrderHandlingInst(string, e.g. F)" << std::endl;
    std::cin >> custOrderHandlingInst;
    std::cout << "Input OrderQty(int)" << std::endl;
    std::cin >> orderQty;
    std::cout << "Input OrdType(char  1=Market 2=Limit 3=Stop 4=Stop-limit K=Market-Limit" << std::endl;
    std::cin >> ordType;
    std::cout << "Input Price(double, used in limit orders only)" << std::endl;
    std::cin >> price;
    std::cout << "Input Side(char 1=buy 2=sell)" << std::endl;
    std::cin >> side;
    std::cout << "Input TimeInForce(char 0=Day 1=GTC 3=FAK 6=GTD)" << std::endl;
    std::cin >> timeInForce;
    std::cout << "Input StopPx(double/0 if N/A)" << std::endl;
    std::cin >> stopPx;
    std::cout << "Input SecurityDesc(string)" << std::endl;
    std::cin.ignore(1024, '\n');
    std::getline(std::cin, securityDesc);
    std::cout << "Input MinQty(int/0 if N/A)" << std::endl;
    std::cin >> minQty;
    std::cout << "Input SecurityType(string)" << std::endl;
    std::cin >> securityType;
    std::cout <<"Input CustomerOrFirm(int/0/1)" << std::endl;
    std::cin >> customerOrFirm;
    std::cout << "Input MaxShow(int/OrdQty if N/A)" << std::endl;
    std::cin >> maxShow;
    std::cout << "Input ExpireDate(string/YYYYMMDD, used in GTD only)" << std::endl;
    std::cin >> expireDate;
    std::cout << "Input ManualOrderIndicator(bool)" << std::endl;
    std::cin >> manualOrderIndicator;
    std::cout << "Enable IFM(Y/N)" << std::endl;
    std::cin >> IFMFlag;
    std::cout <<"Input GiveUpFirm(str(3), NA if N/A)" << std::endl;
    std::cin >> giveUpFirm;
    std::cout << "Input CmtaGiveupCD(GU/SX(NA if N/A))" << std::endl;
    std::cin >> cmtaGiveupCD;
    std::cout << "Input allocAccount(str(11), NA if N/A)" << std::endl;
    std::cin >> allocAccount;

    std::cout << "Confirm? (Y/N):";
    char yesNo;
    std::cin >>yesNo;
    if(yesNo != 'Y')
        return;

    auto res = cmeApplication.sendOrderCancelReplaceRequest(cmeApplication.getSessionIDbyTargetCompID("CME"),
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
    );
    if(res)
        std::cout << "order " << clOrdID << " sent" << std::endl;
    else
        std::cout << "order " << clOrdID << " not sent" << std::endl;
}

void sendOrderMassActionRequest(CMEApplication& cmeApplication){
    std::string clOrdID;
    int32_t massActionScope;
    int32_t marketSegmentID;
    std::string symbol;
    std::string securityDesc;
    int32_t massCancelRequestType;
    std::string account;
    char side;
    char ordType;
    char timeInForce;
    bool manualOrderIndicator;

    std::cout << "Input ClOrdID(string)" << std::endl;
    std::cin >> clOrdID;
    std::cout << "Input MassActionScope(1=Instrument 9=MarketSegmentID 10=Instrument Group)" << std::endl;
    std::cin >> massActionScope;
    std::cout << "Input MarketSegmentID(0 if N/A)" << std::endl;
    std::cin >> marketSegmentID;
    std::cout << "Input Symbol(empty if N/A)" << std::endl;
    std::cin >> symbol;
    std::cout << "Input SecurityDesc(empty if N/A)" << std::endl;
    std::cin.ignore(1024, '\n');
    std::getline(std::cin, securityDesc);
    std::cout << "Input massCancelRequestType(100=SenderSubID 101=Account, 0 if N/A)" << std::endl;
    std::cin >> massCancelRequestType;
    std::cout << "Input Account(empty if N/A" << std::endl;
    std::cin >> account;
    std::cout << "Input Side(char 1=buy 2=sell, 0 if N/A)" << std::endl;
    std::cin >> side;
    std::cout << "Input OrdType(char 2=Limit 4=Stop-limit 0 if N/A" << std::endl;
    std::cin >> ordType;
    std::cout << "Input TimeInForce(char 0=Day 1=GTC 6=GTD, N if N/A)" << std::endl;
    std::cin >> timeInForce;
    std::cout << "Input ManualOrderIndicator(bool)" << std::endl;
    std::cin >> manualOrderIndicator;

    std::cout << "Confirm? (Y/N):";
    char yesNo;
    std::cin >>yesNo;
    if(yesNo != 'Y')
        return;

    auto res = cmeApplication.sendOrderMassActionRequest(cmeApplication.getSessionIDbyTargetCompID("CME"),
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
    );
    if(res)
        std::cout << "order " << clOrdID << " sent" << std::endl;
    else
        std::cout << "order " << clOrdID << " not sent" << std::endl;
}

void sendOrderMassStatusReport(CMEApplication& cmeApplication){
    std::string massStatusReqID;
    int32_t massStatusReqType;
    int32_t marketSegmentID;
    int32_t ordStatusReqType;
    std::string account;
    std::string symbol;
    std::string securityDesc;
    char timeInForce;
    bool manualOrderIndicator;

    std::cout << "Input massStatusReqID(string)" << std::endl;
    std::cin >> massStatusReqID;
    std::cout << "Input MassStatusreqType(1=Instrument 3=Instrument Group 7=All Orders 100=Market Segment" << std::endl;
    std::cin >> massStatusReqType;
    std::cout << "Input MarketSegmentID(0 if N/A)" << std::endl;
    std::cin >> marketSegmentID;
    std::cout << "Input ordStatusReqType(100=SenderSubID 101=Account, 0 if N/A)" << std::endl;
    std::cin >> ordStatusReqType;
    std::cout << "Input Account(empty if N/A" << std::endl;
    std::cin >> account;
    std::cout << "Input Symbol(empty if N/A)" << std::endl;
    std::cin >> symbol;
    std::cout << "Input SecurityDesc(empty if N/A)" << std::endl;
    std::cin.ignore(1024, '\n');
    std::getline(std::cin, securityDesc);
    std::cout << "Input TimeInForce(char 0=Day 1=GTC 6=GTD, N if N/A)" << std::endl;
    std::cin >> timeInForce;
    std::cout << "Input ManualOrderIndicator(bool)" << std::endl;
    std::cin >> manualOrderIndicator;

    std::cout << "Confirm? (Y/N):";
    char yesNo;
    std::cin >>yesNo;
    if(yesNo != 'Y')
        return;

    auto res = cmeApplication.sendOrderMassStatusReport(cmeApplication.getSessionIDbyTargetCompID("CME"),
                                                        massStatusReqID,
                                                        massStatusReqType,
                                                        marketSegmentID,
                                                        ordStatusReqType,
                                                        account,
                                                        symbol,
                                                        securityDesc,
                                                        timeInForce,
                                                        manualOrderIndicator
    );
    if(res)
        std::cout << "massStatusReqID " << massStatusReqID << " sent" << std::endl;
    else
        std::cout << "massStatusReqID " << massStatusReqID << " not sent" << std::endl;
}

void sendQuoteRequest(CMEApplication& cmeApplication){
    std::string quoteReqID;
    std::string symbol;
    int32_t orderQty;
    char side;
    std::string securityDesc;
    std::string securityType;
    std::string custOrderHandlingInst;
    bool manualOrderIndicator;

    std::cout << "Input quoteReqID(string)" << std::endl;
    std::cin >> quoteReqID;
    std::cout << "Input Symbol(empty if N/A)" << std::endl;
    std::cin >> symbol;
    std::cout << "Input OrderQty(int)" << std::endl;
    std::cin >> orderQty;
    std::cout << "Input Side(char 1=buy 2=sell)" << std::endl;
    std::cin >> side;
    std::cout << "Input SecurityDesc(string)" << std::endl;
    std::cin.ignore(1024, '\n');
    std::getline(std::cin, securityDesc);
    std::cout << "Input SecurityType(string)" << std::endl;
    std::cin >> securityType;
    std::cout << "Input custOrderHandlingInst(string, e.g. F)" << std::endl;
    std::cin >> custOrderHandlingInst;
    std::cout << "Input ManualOrderIndicator(bool)" << std::endl;
    std::cin >> manualOrderIndicator;

    std::cout << "Confirm? (Y/N):";
    char yesNo;
    std::cin >>yesNo;
    if(yesNo != 'Y')
        return;

    auto res = cmeApplication.sendQuoteRequest(cmeApplication.getSessionIDbyTargetCompID("CME"),
                                               quoteReqID,
                                               symbol,
                                               orderQty,
                                               side,
                                               securityDesc,
                                               securityType,
                                               custOrderHandlingInst,
                                               manualOrderIndicator
    );

    if(res)
        std::cout << "quoteReqID " << quoteReqID << " sent" << std::endl;
    else
        std::cout << "quoteReqID " << quoteReqID << " not sent" << std::endl;
}

void sendQuoteCancel(CMEApplication& cmeApplication){
    std::string quoteID;
    int32_t quoteCancelType;
    bool manualOrderIndicator;
    int32_t noQuoteEntries;
    std::vector<QuoteCancelEntry> quoteCancelEntries;

    std::cout << "Input quoteID(string)" << std::endl;
    std::cin >> quoteID;
    std::cout << "Input QuoteCancelType(1/3/4/100)" << std::endl;
    std::cin >> quoteCancelType;
    std::cout << "Input ManualOrderIndicator(bool)" << std::endl;
    std::cin >> manualOrderIndicator;
    std::cout << "Input NoQuoteEntries(int)" << std::endl;
    std::cin >> noQuoteEntries;
    for(int32_t i = 0; i < noQuoteEntries; ++i){
        falcon::cme::QuoteCancelEntry quoteCancelEntry;

        std::cout << "Input Symbol for entry " << i << std::endl;
        std::cin >> quoteCancelEntry.symbol_;
        std::cout << "Input SecurityDesc for entry " << i << std::endl;
        std::cin >> quoteCancelEntry.securityDesc_;
        std::cout << "Input QuoteSetID for entry " << i << std::endl;
        std::cin >> quoteCancelEntry.quoteSetID_;

        quoteCancelEntries.push_back(quoteCancelEntry);
    }

    std::cout << "Confirm? (Y/N):";
    char yesNo;
    std::cin >>yesNo;
    if(yesNo != 'Y')
        return;

    auto res = cmeApplication.sendQuoteCancel(cmeApplication.getSessionIDbyTargetCompID("CME"),
                                              quoteID,
                                              quoteCancelType,
                                              manualOrderIndicator,
                                              noQuoteEntries,
                                              quoteCancelEntries
    );

    if(res)
        std::cout << "quoteID " << quoteID << " sent" << std::endl;
    else
        std::cout << "quoteID " << quoteID << " not sent" << std::endl;

}

void sendMassQuote(CMEApplication& cmeApplication){
    std::string quoteReqID;
    std::string quoteID;
    std::string MMAccount;
    bool manualOrderIndicator;
    std::string custOrderHandlingInst;
    int32_t customerOrFirm;
    int32_t NoQuoteSets;
    std::vector<QuoteSet> quoteSets;

    std::cout << "Input quoteReqID(string), empty if N/A" << std::endl;
    std::cin >> quoteReqID;
    std::cout << "Input quoteID(string)" << std::endl;
    std::cin >> quoteID;
    std::cout << "Input MMAccount(string)" << std::endl;
    std::cin >> MMAccount;
    std::cout << "Input ManualOrderIndicator(bool)" << std::endl;
    std::cin >> manualOrderIndicator;
    std::cout << "Input custOrderHandlingInst(string)" << std::endl;
    std::cin >> custOrderHandlingInst;
    std::cout <<"Input CustomerOrFirm(int/0/1)" << std::endl;
    std::cin >> customerOrFirm;
    std::cout <<"Input NoQuoteSets(int)" << std::endl;
    std::cin >> NoQuoteSets;

    for(int32_t i = 0; i < NoQuoteSets; ++i){
        falcon::cme::QuoteSet myQuoteSet;
        std::cout << "Input QuoteSetID for set " << i << std::endl;
        std::cin >> myQuoteSet.quoteSetID_;
        std::cout << "Input UnderlyingSecurityDesc for set " << i << std::endl;
        std::cin >> myQuoteSet.underlyingSecurityDesc_;
        std::cout << "Input NoQuoteEntries for set " << i << std::endl;
        std::cin >> myQuoteSet.NoQuoteEntries_;
        for(int32_t j = 0; j < myQuoteSet.NoQuoteEntries_; ++j){
            falcon::cme::QuoteEntry quoteEntry;
            std::cout << "Input QuoteEntryID for entry " << j << std::endl;
            std::cin >> quoteEntry.quoteEntryID_;
            std::cout << "Input SecurityDesc for entry " << j << std::endl;
            std::cin >> quoteEntry.securityDesc_;
            std::cout << "Input SecurityType for entry " << j << std::endl;
            std::cin >> quoteEntry.securityType_;
            std::cout << "Input SecurityID(0 if NA) for entry" << j << std::endl;
            std::cin >> quoteEntry.securityID_;
            std::cout << "Input BidPx for entry " << j << std::endl;
            std::cin >> quoteEntry.bidPx_;
            std::cout << "Input BidSize for entry " << j << std::endl;
            std::cin >> quoteEntry.bidSize_;
            std::cout << "Input OfferPx for entry " << j << std::endl;
            std::cin >> quoteEntry.offerPx_;
            std::cout << "Input OfferSize for entry " << j << std::endl;
            std::cin >> quoteEntry.offerSize_;

            myQuoteSet.quoteEntries_.push_back(quoteEntry);
        }

        quoteSets.push_back(myQuoteSet);
    }

    std::cout << "Confirm? (Y/N):";
    char yesNo;
    std::cin >>yesNo;
    if(yesNo != 'Y')
        return;

    auto res = cmeApplication.sendMassQuote(cmeApplication.getSessionIDbyTargetCompID("CME"),
                                       quoteReqID,
                                       quoteID,
                                       MMAccount,
                                       manualOrderIndicator,
                                       custOrderHandlingInst,
                                       customerOrFirm,
                                       NoQuoteSets,
                                       quoteSets
    );

    if(res)
        std::cout << "quoteID " << quoteID << " sent" << std::endl;
    else
        std::cout << "quoteID " << quoteID << " not sent" << std::endl;

}

void sendUDSRequest(CMEApplication& cmeApplication){
    std::string securityReqID;
    bool manualOrderIndicator;
    std::string securitySubType;
    int32_t noLegs;
    int32_t legOptionSize;
    std::vector<LegOption> legOption;
    int32_t legFutureSize;
    std::vector<LegFuture> legFuture;
    std::string legSymbol;
    std::string legSecurityDesc;
    char legSide;
    int32_t legRatioQty;
    double legOptionRatio;
    double legPrice;

    std::cout << "Input securityReqID(string), empty if N/A" << std::endl;
    std::cin >> securityReqID;
    std::cout << "Input securitySubType(string)" << std::endl;
    std::cin >> securitySubType;
    std::cout << "Input ManualOrderIndicator(bool)" << std::endl;
    std::cin >> manualOrderIndicator;
    std::cout <<"Input legOptionSize(int)" << std::endl;
    std::cin >> legOptionSize;
    std::cout <<"Input legFutureSize(int)" << std::endl;
    std::cin >> legFutureSize;
    noLegs = legOptionSize + legFutureSize;

    std::cout << "Input for option leg set " << std::endl;
    for(int32_t j = 0; j < legOptionSize; ++j){
        falcon::cme::LegOption optionEntry;
        std::cout << "Input LegSymbol for entry " << j << std::endl;
        std::cin >> optionEntry.legSymbol_;
        std::cout << "Input LegSecurityDesc for entry " << j << std::endl;
        std::cin >> optionEntry.legSecurityDesc_;
        std::cout << "Input LegRatioQty for entry " << j << std::endl;
        std::cin >> optionEntry.legRatioQty_;
        std::cout << " Input Side(char 1=buy 2=sell) for entry" << j << std::endl;
        std::cin >> optionEntry.legSide_;
        legOption.push_back(optionEntry);
    }
    std::cout << "Input for future leg set " << std::endl;
    for(int32_t j = 0; j < legFutureSize; ++j){
        falcon::cme::LegFuture futureEntry;
        std::cout << "Input LegSymbol for entry " << j << std::endl;
        std::cin >> futureEntry.legSymbol_;
        std::cout << "Input LegSecurityDesc for entry " << j << std::endl;
        std::cin >> futureEntry.legSecurityDesc_;
        std::cout << "Input LegOptionRatio for entry " << j << std::endl;
        std::cin >> futureEntry.legOptionRatio_;
        std::cout << " Input Side(char 1=buy 2=sell) for entry" << j << std::endl;
        std::cin >> futureEntry.legSide_;
        std::cout << "Input LegPrice for entry " << j << std::endl;
        std::cin >> futureEntry.legPrice_;

        legFuture.push_back(futureEntry);
    }

    std::cout << "Confirm? (Y/N):";
    char yesNo;
    std::cin >>yesNo;
    if(yesNo != 'Y')
        return;

    auto res = cmeApplication.sendSecurityDefinitionRequest(cmeApplication.getSessionIDbyTargetCompID("CME"),
                                            manualOrderIndicator,
                                            securityReqID,
                                            securitySubType,
                                            noLegs,
                                            legOptionSize,
                                            legOption,
                                            legFutureSize,
                                            legFuture
    );

    if(res)
        std::cout << "securityReqID " << securityReqID << " sent" << std::endl;
    else
        std::cout << "securityReqID " << securityReqID << " not sent" << std::endl;

}

void sendNewOrderCross(CMEApplication& cmeApplication){
    double price;
    std::string symbol;
    bool manualOrderIndicator;
    std::string securityDesc;
    std::string securityType;
    std::string crossID;
    std::vector<CrossEntry> crossEntries;

    std::cout << "Input Symbol" << std::endl;
    std::cin >> symbol;
    std::cout << "Input SecurityDesc" << std::endl;
    std::cin.ignore(1024,'\n');
    std::getline(std::cin, securityDesc);
    std::cout << "Input SecurityType" << std::endl;
    std::cin >> securityType;
    std::cout << "Input CrossID" << std::endl;
    std::cin >> crossID;
    std::cout << "Input Price(double)" << std::endl;
    std::cin >> price;
    std::cout << "Input ManualOrderIndicator(bool)" << std::endl;
    std::cin >> manualOrderIndicator;

    for(int32_t i = 0; i < 2; ++i) {
        falcon::cme::CrossEntry crossEntry;

        std::cout << "Input side(1=Buy 2=Sell) for entry " << i << std::endl;
        std::cin >> crossEntry.side_;
        std::cout << "Input account for entry " << i << std::endl;
        std::cin >> crossEntry.account_;
        std::cout << "Input ClOrdID for entry " << i << std::endl;
        std::cin >> crossEntry.clOrdID_;
        std::cout << "Input custOrderHandlingInst for entry " << i << std::endl;
        std::cin >> crossEntry.custOrderHandlingInst_;
        std::cout << "Input OrderQty for entry " << i << std::endl;
        std::cin >> crossEntry.orderQty_;
        std::cout << "Input sideTimeInForce for entry " << i << std::endl;
        std::cin >> crossEntry.sideTimeInForce_;
        std::cout << "Input customerOrFirm for entry " << i << std::endl;
        std::cin >> crossEntry.customerOrFirm_;

        crossEntries.push_back(crossEntry);
    }

    auto res = cmeApplication.sendNewOrderCross(cmeApplication.getSessionIDbyTargetCompID("CME"),
                                                price,
                                                symbol,
                                                manualOrderIndicator,
                                                securityDesc,
                                                securityType,
                                                crossID,
                                                crossEntries
    );
    if(res)
        std::cout << "crossID " << crossID << " sent" << std::endl;
    else
        std::cout << "crossID " << crossID << " not sent" << std::endl;
}

void printMenu(){
    std::cout << "Welcome to Falcon!"<< std::endl;
    std::cout << "Please select the action(Input Q to quit and C to clear and print menu): " << std::endl;
    std::cout << "A: Send Test Request" << std::endl;
    std::cout << "C: Clear screen" << std::endl;
    std::cout << "D: Place New Order" << std::endl;
    std::cout << "E: Cancel Order" << std::endl;
    std::cout << "F: Amend Order" << std::endl;
    std::cout << "G: Send Mass Action Request" << std::endl;
    std::cout << "H: Send Order Mass Status Report" << std::endl;
    std::cout << "I: Send Quote Request" << std::endl;
    std::cout << "J: Send Quote Cancel" << std::endl;
    std::cout << "K: Send Mass Quote" << std::endl;
    std::cout << "L: Send UDS request" << std::endl;
    std::cout << "M: Send New Order Cross" << std::endl;
    std::cout << "N: Send Multiple Orders" << std::endl;
    std::cout << "Q: Log out" << std::endl;
}

void getMenu(CMEApplication& cmeApplication){
    std::cout << "\033c";
    printMenu();
    while(true){
        auto c = getchar();
        if(c == 'Q') {
            std::cout << "Quiting and Logout..." << std::endl;
            cmeApplication.stop(false);

            sleep(6);
            break;
        }
        else if(c == 'C'){
            std::cout << "\033c";
            printMenu();
        }
        else if(c == 'A'){
           sendTestRequest(cmeApplication);
        }
        else if(c == 'D'){
            placeNewOrder(cmeApplication);
        }
        else if(c == 'E'){
            cancelOrder(cmeApplication);
        }
        else if(c == 'F'){
            amendOrder(cmeApplication);
        }
        else if(c == 'G'){
            sendOrderMassActionRequest(cmeApplication);
        }
        else if(c == 'H'){
            sendOrderMassStatusReport(cmeApplication);
        }
        else if(c == 'I'){
            sendQuoteRequest(cmeApplication);
        }
        else if(c == 'J'){
            sendQuoteCancel(cmeApplication);
        }
        else if(c == 'K'){
            sendMassQuote(cmeApplication);
        }
        else if(c == 'L'){
            sendUDSRequest(cmeApplication);
        }
        else if(c == 'M') {
            sendNewOrderCross(cmeApplication);
        }
        else if (c == 'N'){
            sendMultipleOrders(cmeApplication);
        }
        else if(c != '\n'){
            std::cout << "Invalid command, please try again!" << std::endl;
        }
    }
}

int main() {
    LOG("Starting the main server...");

    try {
        CMEApplication cmeApplication("../config/CMEiLink.ini");
        CMEGateWay cmeGateWay;

        cmeGateWay.setCMESessionClient(&cmeApplication, "CME");

        cmeGateWay.start();

        getMenu(cmeApplication);
        //cmeGateWay.stop();
    }
    catch (ConfigError& e){
        std::cout << e.what() << std::endl;
    }
    catch(std::exception& e){

        std::cout << e.what() << std::endl;
    }

//    falcon::db::DBConnection* dbConnection = new falcon::db::MySQLConn("127.0.0.1", 3306, "root", "Goodyear");


    /////////////////////////////////
    /*  New CMEGateway
     *  New Connection
     *  New DBConn
     *  New OrderRequestMgr and Add CMEGateway
     *  New ActiveOrderMgr and register it to CMEGateway
     *  start CME session connection
     *
     *
     *
     * shutdown
     *
     */
    return 0;
}
