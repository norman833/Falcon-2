
#ifndef FALCON_MDMANAGER_H
#define FALCON_MDMANAGER_H

#include <unordered_map>
#include "MDOrderBook.h"

namespace falcon {
    namespace md{
        class MDManager{
        public:
            MDManager();
            virtual ~MDManager();

        private:
            std::unordered_map<std::string, MDOrderBook> map_;
        };
    } //namespace md
} //namespace falcon

#endif //FALCON_MDMANAGER_H
