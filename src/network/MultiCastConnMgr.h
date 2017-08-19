
#ifndef FALCON_MULTICASTCONNMGR_H
#define FALCON_MULTICASTCONNMGR_H

#include <string>
#include <cstdint>
/*
#include <boost/asio.hpp>

#include "NetworkEventProcessorInf.h"

namespace falcon {
    namespace network {
        class MultiCastConnMgr {
        public:
            MultiCastConnMgr(const std::string& listen_ip, const std::string& multicast_ip, uint32_t port);
            virtual ~MultiCastConnMgr();

            virtual void onEvent(const boost::system::error_code& error, // Result of operation.
                                 std::size_t bytes_transferred          // Number of bytes received.
                                );
            virtual bool connect();
            virtual bool disconnect();
            virtual bool isConncted();

            virtual void registerObserver(NetworkEventProcessorInf* observer);
            virtual void removeObserver(NetworkEventProcessorInf* observer);

        private:
            bool started_;

            uint32_t port_;
            boost::asio::ip::address listen_address_;
            boost::asio::ip::address multicast_address_;

            boost::asio::io_service io_service_;
            boost::asio::ip::udp::socket socket_;
            boost::asio::ip::udp::endpoint sender_endpoint_;
            boost::asio::ip::udp::endpoint listen_endpoint_;

            enum { max_length = 1024 * 1024 };
            char data_[max_length];

            std::vector<NetworkEventProcessorInf* > observers_;
        };
    }// namespace network
}// namespace falcon

*/
#endif //FALCON_MULTICASTCONNMGR_H
