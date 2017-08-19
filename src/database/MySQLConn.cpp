#include "MySQLConn.h"
#include <iostream>
#include <sstream>
namespace falcon {
    namespace db {
        bool MySQLConn::connect() {

            std::stringstream sstream;

            sstream << "tcp://" << ip_ << ":" << port_;
            /*
            driver_ = sql::mysql::get_mysql_driver_instance();

            con_ = driver_->connect(sstream.str(), user_, password_);
            */
            std::cout << sstream.str() << std::endl;
            return true;
        }
        bool MySQLConn::disconnect() {

            return true;
        };
    }// namespace db
}// namespace falcon