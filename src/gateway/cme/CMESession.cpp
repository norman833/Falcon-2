#include "CMESession.h"
namespace falcon {
    namespace cme {
        using  namespace FIX;

        CMESession::CMESession(Application& application, std::string settingFile) :
                settings_(settingFile), storeFactory_(settings_), logFactory_(settings_),
                socketInitiator_(application, storeFactory_, settings_, logFactory_){
        };

        bool CMESession::start() {
            this->socketInitiator_.start();
            return true;
        };

        bool CMESession::stop(bool force) {
            this->socketInitiator_.stop(force);
            return true;
        }
    } //namespace cme
} //namespace falcon