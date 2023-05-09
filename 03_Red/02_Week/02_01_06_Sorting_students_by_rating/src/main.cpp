#include "student.h"
#include "test_runner.h"
#include "tests.h"
#include "profile.h"

using namespace std;

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestComparison);
    RUN_TEST(tr, TestSorting);

    {
        LOG_DURATION("MyTest1");
        RUN_TEST(tr, MyTest1);
    }

    {
        LOG_DURATION("MyTest2");
        RUN_TEST(tr, MyTest2);
    }
    return 0;
}