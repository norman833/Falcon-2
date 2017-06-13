#include <iostream>
#include <boost/log/trivial.hpp>

int main() {
    std::cout << "Hello, World!" << std::endl;
   // BOOST_LOG_TRIVIAL(trace) << "A trace severity message";
    BOOST_LOG_TRIVIAL(fatal) << "A fatal error!";
    return 0;
}