//#include <iostream>
#include "base/Logger.h"
#include "database/DatabaseTask.h"
#include "base/INIParser.h"

int main() {

    falcon::db::DatabaseTask dt;

    falcon::base::INIParser parser;

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
