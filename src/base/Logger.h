
#ifndef FALCON_LOGGER_H
#define FALCON_LOGGER_H

#include <string>
#include <sstream>
#include <ctime>

#include "Log.h"
namespace log{
    static std::string getGlobalLogName(){
        std::stringstream ss;
        std::time_t result = std::time(nullptr);
        std::string str = std::string(std::ctime(&result));
        ss << "FalconLog " << str.substr(0, str.size()-1) << ".log";

        return ss.str();
    };
}

static falcon::base::logger< falcon::base::file_log_policy > log_inst( log::getGlobalLogName() );

#ifdef LOGGING_LEVEL_1
#define LOG log_inst.print< falcon::base::severity_type::debug >
#define LOG_ERR log_inst.print< falcon::base::severity_type::error >
#define LOG_WARN log_inst.print< falcon::base::severity_type::warning >
#else
#define LOG(...)
#define LOG_ERR(...)
#define LOG_WARN(...)
#endif

#ifdef LOGGING_LEVEL_2
#define ELOG log_inst.print< falcon::base::severity_type::debug >
#define ELOG_ERR log_inst.print< falcon::base::severity_type::error >
#define ELOG_WARN log_inst.print< falcon::base::severity_type::warning >
#else
#define ELOG(...)
#define ELOG_ERR(...)
#define ELOG_WARN(...)
#endif

#endif //FALCON_LOGGER_H
