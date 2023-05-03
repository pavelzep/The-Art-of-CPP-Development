#include "test_runner.h"
#include "deque.h"
#include "my_test.h"

int main() {
    TestRunner tr;
    RUN_TEST(tr, MyTest);

    return 0;
}
