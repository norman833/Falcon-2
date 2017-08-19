#ifndef FALCON_NETWORKEVENTPROCESSORINF_H
#define FALCON_NETWORKEVENTPROCESSORINF_H

namespace falcon {
    namespace network {
        class NetworkEventProcessorInf {
        public:
            NetworkEventProcessorInf() {};
            virtual ~NetworkEventProcessorInf() {};

            virtual void processEvent(const std::string & data) = 0;
        };
    } //namespace network
} //namespace falcon

#endif //FALCON_NETWORKEVENTPROCESSORINF_H
