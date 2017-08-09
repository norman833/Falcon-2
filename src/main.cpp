#include <string>
#include <ctime>

#include "CMEFIX_router.hpp"
#include "CMEFIX_classes.hpp"

#include "CMEGateWay.h"
#include "CMESessionClient.h"
std::string getGlobalLogName(){
    std::stringstream ss;
    std::time_t result = std::time(nullptr);
    std::string str = std::string(std::ctime(&result));
    ss << "FalconLog " << str.substr(0, str.size()-1) << ".log";

    return ss.str();
};

int main() {

    using namespace FIX8;
    using namespace falcon;
    using namespace falcon::cme;

    std::string logName = getGlobalLogName();

    GlobalLogger::set_global_filename(logName);

    glout_error << "Falcon Starting...";
    glout_fatal << "test fatal error " << 999;
    glout_info << "fyi " << 0;

    ReliableCMESessionClient cmeSessionClient(FIX8::CMEFIX::ctx(), "session.xml", "DLD1" );
    glout_info << "Session name is " << cmeSessionClient._session_name;

    cmeSessionClient.start(true);

    CMEGateWay cmeGateWay;

    cmeGateWay.setCMESessionClient(&cmeSessionClient);

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
