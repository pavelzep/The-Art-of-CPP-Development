#include "test_runner.h"
#include "tests.h"

void TestAll() {
    TestRunner tr;
    RUN_TEST(tr, TestAddingNewObjectOnMap);
}

int main() {
    TestAll();
    return 0;
}

