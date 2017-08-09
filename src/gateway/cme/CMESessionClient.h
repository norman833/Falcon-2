#ifndef FALCON_CMESESSIONCLIENT_H
#define FALCON_CMESESSIONCLIENT_H

#include "CMEMsgRouter.h"

#include "fix8/f8includes.hpp"
#include "fix8/sessionwrapper.hpp"

namespace falcon {
    namespace cme {

        using namespace FIX8;

        class CMESessionClient : public Session {
        public:
            CMESessionClient(const F8MetaCntx& ctx, const SessionID& sid, Persister *persist=nullptr,
                             Logger *logger=nullptr, Logger *plogger=nullptr):
                    Session(ctx, sid, persist, logger, plogger), router_(*this){};

            virtual bool handle_application(const unsigned seqnum, const FIX8::Message *&msg);

        private:
            CMEMsgRouter router_;
        };

        class ReliableCMESessionClient : public ReliableClientSession<CMESessionClient>{
        public:
            ReliableCMESessionClient(const F8MetaCntx& ctx, const std::string& conf_file, const std::string& session_name) :
                    ReliableClientSession<CMESessionClient>(ctx, conf_file, session_name){};
        private:
        };
    } //namespace cme
} //namespace falcon


#endif //FALCON_CMESESSIONCLIENT_H
