#include "TCPConnMgr.h"
/*
namespace falcon {
    namespace network {
        TCPConnMgr::TCPConnMgr(const std::string& server_ip, uint32_t port) :
                server_address_(boost::asio::ip::address::from_string(server_ip)),
                server_port_(port),
                socket_(io_service_)
        {


        };

        TCPConnMgr::~TCPConnMgr() {
            if(isConnected())
                disconnect();
        }

        bool TCPConnMgr::connect() {
            if(!isConnected()){

                //this->socket_.
                this->started_ = true;
            }
            return true;
        };

        bool TCPConnMgr::disconnect() {
            if(isConnected()){

                this->socket_.close();
                this->started_ = false;
            }

            return true;
        };

        bool TCPConnMgr::isConnected() {
            return(this->started_);
        }

        void TCPConnMgr::sendMsg(const std::string &msg) {
            this->socket_.send(boost::asio::buffer(msg, msg.size()));
        }

    } //namespace network
} //namespace falcon
 */