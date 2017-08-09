#ifndef FALCON_DBCONNECTION_H
#define FALCON_DBCONNECTION_H


namespace falcon {
    namespace db {
        class DBConnection {
        public:
            virtual bool connect() = 0;
            virtual bool disconnect() = 0;
        };
    }// namespace db
}// namespace falcon

#endif //FALCON_DBCONNECTION_H
