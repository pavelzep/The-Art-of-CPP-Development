#include "test_runner.h"
#include "matrix.h"
#include "tests.h"

using namespace std;

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestCalculateMatrixSum);
}
