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
                                      manualOrderIndicator
    );

    if(res)
        std::cout << "order " << clOrdID << " sent" << std::endl;
    else
        std::cout << "order " << clOrdID << " not sent" << std::endl;
}

void amendOrder(CMEApplication& cmeApplication)
{
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
                                                       IFMFlag
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

void printMenu(){
    std::cout << "Welcome to Falcon!"<< std::endl;
    std::cout << "Please select the action(Input Q to quit and C to clear and print menu): " << std::endl;
    std::cout << "A: Send Test Request" << std::endl;
    std::cout << "C: Clear screen" << std::endl;
    std::cout << "D: Place New Order" << std::endl;
    std::cout << "E: Cancel Order" << std::endl;
    std::cout << "F: Amend Order" << std::endl;
    std::cout << "G: Send Mass Action Request" << std::endl;
    std::cout << "H: Send OrderMassStatusReport" << std::endl;
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

        cmeGateWay.setCMESessionClient(&cmeApplication);

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
