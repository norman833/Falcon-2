
#ifndef FALCON_MDCONNINF_H
#define FALCON_MDCONNINF_H

namespace falcon {
    namespace md{
        class MDConnInf {
        public:
            MDConnInf(){};
            virtual ~MDConnInf(){};

            virtual getMDConn() = 0;
        private:
        };
    } //namespace md
} //namespace falcon


#endif //FALCON_MDCONNINF_H
