#ifndef FALCON_CMESESSION_H
#define FALCON_CMESESSION_H

#include <string>

#include "quickfix/FileStore.h"
#include "quickfix/FileLog.h"
#include "quickfix/Session.h"
#include "quickfix/SessionSettings.h"
#include "quickfix/SocketInitiator.h"

namespace falcon {
    namespace cme {
        using  namespace FIX;

        class CMESession {
        public:
            CMESession(Application& application, std::string settingFile);
            virtual bool start();
            virtual bool stop(bool force = false);
            virtual bool sendLogon();
        private:
            SessionSettings settings_;
            FileStoreFactory storeFactory_;
            FileLogFactory logFactory_;
            SocketInitiator socketInitiator_;
        };
    } //namespace cme
} //namespace falcon

#endif //FALCON_CMESESSION_H
