#include "CMESessionClient.h"
namespace falcon {
    namespace cme {
        using namespace FIX8;
        CMESessionClient::CMESessionClient(const F8MetaCntx &ctx, const SessionID &sid, Persister *persist,
                                           Logger *logger, Logger *plogger)
                : Session( ctx, sid, persist, logger, plogger)  {

        };

        bool CMESessionClient::handle_application(const unsigned seqnum, const Message *&msg) {
            //this->_logger << "Got a non admin msg, processing..."  << seqnum << "\n";
            return true;
        }
    } //namespace cme
} //namespace falcon

