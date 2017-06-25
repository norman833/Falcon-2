
#ifndef FALCON_MULTICASTCONNMGR_H
#define FALCON_MULTICASTCONNMGR_H

#include <string>
#include <cstdint>
#include <boost/asio.hpp>

namespace falcon {
    namespace network {

        class MultiCastConnMgr {
        public:
            MultiCastConnMgr(const std::string& ip, uint32_t port) {};
            virtual ~MultiCastConnMgr();

            virtual void connect();
            virtual void disconnect();

        private:
            virtual bool initialized();

            bool flag_;
            std::string ip_;
            uint32_t port_;
        };
    }// namespace network
}// namespace falcon


#endif //FALCON_MULTICASTCONNMGR_H
