
#include "test_runner.h"
#include "tests.h"

using namespace std;

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestBasic);
    RUN_TEST(tr, TestAbsentParts);
}
