#include <iostream>

namespace falcon{
    namespace test{
        void testDummy();
        void testDummy2();
    }
}

int main() {
    using namespace falcon::test;

    testDummy();
    testDummy2();

    return 0;
}
