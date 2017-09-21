#include <string>
#include <ctime>
#include <sstream>
#include <exception>

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
}

void printMenu(){
    std::cout << "Welcome to Falcon!"<< std::endl;
    std::cout << "Please select the action(Input Q to quit): " << std::endl;
    std::cout << "A: Send Test Request" << std::endl;
}

void getMenu(){
    while(1){
        std::cout << "\033c";
        printMenu();

        auto c = getchar();
        if(c == 'Q'){
            std::cout << "Quiting..." << std::endl;
            break;
        }
        else if(c == 'A'){

        }
        else{
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
        std::cout << "init" << std::endl;
        cmeGateWay.start();

        getMenu();

        sleep(60);

        cmeGateWay.stop();
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
