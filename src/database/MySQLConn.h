#ifndef FALCON_MYSQLCONN_H
#define FALCON_MYSQLCONN_H

#include <DBConnection.h>
/*
#include "mysql_connection.h"
#include "mysql_driver.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
*/

#include <string>
#include <cstdint>
#include <memory>

namespace falcon {
    namespace db {
        class MySQLConn : public  DBConnection{
        public:
            MySQLConn(std::string ip, uint32_t port, std::string user, std::string password) :
            ip_(ip), port_(port), user_(user), password_(password) {};

            virtual bool connect();
            virtual bool disconnect();
        private:
            std::string ip_;
            uint32_t    port_;
            std::string user_;
            std::string password_;
            bool        connected_{false};
            /*
            sql::mysql::MySQL_Driver* driver_;
            sql::Connection* con_;
             */
        };
    }// namespace db
}// namespace falcon

#endif //FALCON_MYSQLCONN_H
