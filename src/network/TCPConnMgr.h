#ifndef FALCON_TCPCONNMGR_H
#define FALCON_TCPCONNMGR_H

#include <string>
#include <cstdint>
/*
#include <boost/array.hpp>
#include <boost/asio.hpp>

namespace falcon {
    namespace network {

        class NetworkEventProcessorInf;

        class TCPConnMgr {
        public:
            TCPConnMgr(const std::string& server_ip, uint32_t port);
            virtual ~TCPConnMgr();
            virtual bool connect();
            virtual bool disconnect();
            virtual bool isConnected();

            virtual void sendMsg(const std::string& msg);
            virtual void receiveMsg();

        private:
            boost::asio::io_service io_service_;
            boost::asio::ip::tcp::socket socket_;


            //boost::asio::ip::tcp::endpoint clinet_endpoint_;
            boost::asio::ip::tcp::endpoint server_endpoint_;
            uint32_t server_port_;
            boost::asio::ip::address server_address_;

            bool started_;
            enum { max_length = 1024 * 1024 };
            char data_[max_length];

            std::vector<NetworkEventProcessorInf* > observers_;
        };
    } //namespace network
} //namespace falcon

*/
#endif //FALCON_TCPCONNMGR_H
