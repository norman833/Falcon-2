#include "CMESessionClient.h"
#include "CMEMsgRouter.h"

namespace falcon {
    namespace cme {
        using namespace FIX8;

        bool CMESessionClientBase::handle_application(const unsigned seqnum, const Message *&msg) {

            return true;
        }
    } //namespace cme
} //namespace falcon

