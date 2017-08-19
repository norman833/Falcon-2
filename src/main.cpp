#include <string>
#include <ctime>
#include <sstream>
#include <exception>

#include "CMEGateWay.h"
#include "CMESession.h"
#include "CMEApplication.h"
#include "Logger.h"

int main() {
    using namespace std;
    using namespace falcon;
    using namespace falcon::cme;

    LOG("Starting the main server...");
    try {
        CMEApplication cmeApplication;
        CMESession cmeSession(cmeApplication, "../config/CMEiLink.ini");
        cmeSession.start();

        sleep(1);
        cmeSession.sendLogon();

        sleep(1);

        cmeSession.stop();
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
