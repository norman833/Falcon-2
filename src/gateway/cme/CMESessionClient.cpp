#include "CMESessionClient.h"

namespace falcon {
    namespace cme {

        bool CMESessionClient::handle_application(const unsigned seqnum, const FIX8::Message *&msg) {
            glout_info << "Processing seqnum " << seqnum << "\n";

            return this->enforce(seqnum, msg) || msg->process(this->router_);
        }
    } //namespace cme
} //namespace falcon

