
#include "MultiCastConnMgr.h"
/*
#include "boost/bind.hpp"

namespace falcon {
    namespace network {

        MultiCastConnMgr::MultiCastConnMgr(const std::string& listen_ip, const std::string& multicast_ip, uint32_t port)
                : listen_address_(boost::asio::ip::address::from_string(listen_ip)),
                  multicast_address_(boost::asio::ip::address::from_string(multicast_ip)),
                  socket_(io_service_),
                  port_(port)
        {
            // Create the socket so that multiple may be bound to the same address.
            boost::asio::ip::udp::endpoint listen_endpoint(listen_address_, port_);

            socket_.open(listen_endpoint.protocol());
            socket_.set_option(boost::asio::ip::udp::socket::reuse_address(true));
            socket_.bind(listen_endpoint);
        };

        MultiCastConnMgr::~MultiCastConnMgr() {
            if(isConncted())
                disconnect();
        }

        bool MultiCastConnMgr::connect() {

            if(isConncted())
                return true;

            this->started_ = true;

            // Join the multicast group.
            socket_.set_option(
                    boost::asio::ip::multicast::join_group(multicast_address_));

            socket_.async_receive_from(
                    boost::asio::buffer(data_, max_length), sender_endpoint_,
                    boost::bind(&MultiCastConnMgr::onEvent,
                                this,
                                boost::asio::placeholders::error,
                                boost::asio::placeholders::bytes_transferred));

            return true;
         };

        bool MultiCastConnMgr::disconnect() {
            if(isConncted()) {
                socket_.set_option(
                        boost::asio::ip::multicast::leave_group(multicast_address_));
                this->started_ = false;
            };

            return true;
        }

        bool MultiCastConnMgr::isConncted() {
            return(this->started_);
        }
        void MultiCastConnMgr::onEvent(const boost::system::error_code& error, // Result of operation.
                                       std::size_t bytes_transferred           // Number of bytes received.
        )
        {
            //TODO callback
            for(auto obsever: this->observers_)
            {
                obsever->processEvent(this->data_);
            }
        };

        void MultiCastConnMgr::registerObserver(NetworkEventProcessorInf *observer) {
            this->observers_.push_back(observer);
        }

        void MultiCastConnMgr::removeObserver(NetworkEventProcessorInf *observer) {
            auto p = this->observers_.begin();

            while(p != this->observers_.end()){
                if( *p == observer){
                    this->observers_.erase(p);
                    break;
                }
                else{
                    ++p;
                }
            }
        }
    } //namespace network
}// namespace falcon
*/