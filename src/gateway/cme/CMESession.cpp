#include "CMESession.h"

#include "quickfix/fix42/Logon.h"
#include "quickfix/Message.h"

namespace falcon {
    namespace cme {
        using  namespace FIX;

        CMESession::CMESession(Application& application, std::string settingFile) :
                settings_(settingFile), storeFactory_(settings_), logFactory_(settings_),
                socketInitiator_(application, storeFactory_, settings_, logFactory_){
        };

        bool CMESession::start() {
            this->socketInitiator_.start();
            std::cout << socketInitiator_.getSessions().size() << std::endl;
            std::cout << socketInitiator_.getSessionSettings(SessionID("FIX.4.2", "ABC123N", "CME"))->getString("BeginString") << std::endl;
            return true;
        };

        bool CMESession::stop(bool force) {
            this->socketInitiator_.stop(force);
            //socketInitiator_.getSessions().begin()->g;
            return true;
        }

        bool CMESession::sendLogon() {
            FIX42::Logon logon;
            //logon.getHeader().set(BeginString(settings_.get().getString("")));
            FIX::Session::sendToTarget(logon, *(socketInitiator_.getSessions().begin()));

            return true;
            //auto header = logon.getHeader();
            //header.set(BeginString());
            //header.set(settings_.get()
        };

    } //namespace cme
} //namespace falcon