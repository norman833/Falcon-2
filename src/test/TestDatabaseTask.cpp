#include <cassert>
#include <iostream>

namespace falcon {
    namespace test {
        void testDummy() {
            assert(true);
            std::cout << "Test passed" << std::endl;
        }
    }
}