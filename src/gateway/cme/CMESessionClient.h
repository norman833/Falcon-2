#ifndef FALCON_CMESESSIONCLIENT_H
#define FALCON_CMESESSIONCLIENT_H

#include "fix8/f8includes.hpp"

namespace falcon {
    namespace cme {
        using namespace FIX8;
        class CMESessionClient : public Session {
        public:
            CMESessionClient(const F8MetaCntx& ctx, const SessionID& sid, Persister *persist=nullptr,
                             Logger *logger=nullptr, Logger *plogger=nullptr);
            virtual bool handle_application(const unsigned seqnum, const Message *&msg);

        };
    } //namespace cme
} //namespace falcon


#endif //FALCON_CMESESSIONCLIENT_H
