#include "CMEMsgRouter.h"
namespace falcon {
    namespace cme {
        bool CMEMsgRouter::operator()(const class Logon *msg) const {
            glout_info << "Receiving Logon msg...\n";
            return  true;
        };

        bool CMEMsgRouter::operator()(const class Logout *msg) const {
            glout_info << "Receiving Logout msg...\n";
            return true;
        };

        bool CMEMsgRouter::operator()(const class Heartbeat *msg) const {
            glout_info << "Receiving Heartbeat msg...\n";
            return true;
        };

        bool CMEMsgRouter::operator()(const class Reject *msg) const {

            return  false;
        };

        bool CMEMsgRouter::operator()(const class SequenceReset *msg) const {

            return false;
        };

        bool CMEMsgRouter::operator()(const class ExecutionReport *msg) const {

            return false;
        };

        bool CMEMsgRouter::operator()(const class NewOrderSingle *msg) const {

            return false;
        };

        bool CMEMsgRouter::operator()(const class NewOrderList *msg) const {

            return false;
        };

        bool CMEMsgRouter::operator()(const class OrderCancelReject *msg) const {

            return false;
        }

        bool CMEMsgRouter::operator()(const class OrderCancelRequest *msg) const {

            return false;
        }

        bool CMEMsgRouter::operator()(const class OrderCancelReplaceRequest *msg) const {

            return false;
        }
    } //namespace cme
} //namespace falcon