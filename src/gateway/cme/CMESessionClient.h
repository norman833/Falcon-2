#ifndef FALCON_CMESESSIONCLIENT_H
#define FALCON_CMESESSIONCLIENT_H

#include "fix8/f8includes.hpp"
#include "fix8/sessionwrapper.hpp"

namespace falcon {
    namespace cme {
        class CMEMsgRouter;

        using namespace FIX8;

        class CMESessionClientBase : public Session {
        public:
            CMESessionClientBase(const F8MetaCntx& ctx, const SessionID& sid, Persister *persist=nullptr,
                             Logger *logger=nullptr, Logger *plogger=nullptr): Session(ctx, sid, persist, logger, plogger){};

            virtual bool handle_application(const unsigned seqnum, const Message *&msg);

        private:
            CMEMsgRouter* cmeMsgRouter_;
        };

        class CMESessionClient : public ReliableClientSession<CMESessionClientBase>{
        public:
            CMESessionClient(const F8MetaCntx& ctx, const std::string& conf_file, const std::string& session_name) :
                    ReliableClientSession(ctx, conf_file, session_name){};
        private:
        };

    } //namespace cme
} //namespace falcon


#endif //FALCON_CMESESSIONCLIENT_H
