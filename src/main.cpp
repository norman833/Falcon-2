#include "base/Logger.h"
#include "base/INIParser.h"

#include "CMEFIX_router.hpp"
#include "CMEFIX_classes.hpp"
#include "CMEFIX_types.hpp"
#include "network/MultiCastConnMgr.h"

#include "fix8/logger.hpp"
#include "MySQLConn.h"
int main() {

    using namespace FIX8;

    CMEFIX::CMEFIX_Router router;
    CMEFIX::Logon logon;

    Logger::LogFlags flag;
    Logger::Levels level;


    FileLogger fileLogger("./fix8log", flag, level );


    glout << "test";

    glout_error << "error";
    glout_fatal << "fatal error " << 999;
    glout_info << "fyi " << 0;

    falcon::db::DBConnection* dbConnection = new falcon::db::MySQLConn("127.0.0.1", 3306, "root", "Goodyear");

    dbConnection->connect();

    falcon::base::INIParser parser;

    falcon::network::MultiCastConnMgr multicast_rec("127.0.0.1", "239.255.0.1", 30001);

    std::cout << "Multicast receiver's connection status: " <<  multicast_rec.isConncted() << std::endl;
    LOG("Starting the application..");
    LOG_ERR("error");
    LOG_WARN("WARN");

    for( short i = 0 ; i < 3 ; i++ )
    {
        LOG("The value of 'i' is ", i , ". " , 3 - i - 1 , " more iterations left ");
    }
    LOG_WARN("Loop over");
    LOG_ERR("All good things come to an end.. :(");

    return 0;
}
