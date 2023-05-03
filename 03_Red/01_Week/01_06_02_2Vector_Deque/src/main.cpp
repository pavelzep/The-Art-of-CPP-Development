
#include "my_test.h"

int main() {
    TestRunner tr;
    RUN_TEST(tr, MyTest);
    RUN_TEST(tr, test_8);
    RUN_TEST(tr, test_9);


    return 0;
}
