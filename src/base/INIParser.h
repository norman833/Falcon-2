#ifndef FALCON_INIPARSER_H
#define FALCON_INIPARSER_H

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

namespace falcon {
    namespace base {
        class INIParser {
        public:
            INIParser(){
                boost::property_tree::ptree pt;
                boost::property_tree::ini_parser::read_ini("../config/MainConfig.ini", pt);
                std::cout << pt.get<std::string>("Section1.Value1") << std::endl;
                std::cout << pt.get<std::string>("Section1.Value2") << std::endl;
            }
        };
    };// namespace base
};// namespace falcon


#endif //FALCON_INIPARSER_H
