#include <string>
#include <ctime>
#include <sstream>

#include "CMEGateWay.h"
#include "CMEQFClient.h"
#include "Logger.h"

int main() {
    using namespace std;
    using namespace falcon;
    using namespace falcon::cme;

    LOG("Starting the main server...");

    CMEQFClient cmeqfClient;

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
