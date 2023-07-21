#include "test_runner.h"
#include "paginator.h"
#include <vector>
#include <future>

using namespace std;

int64_t CalculateMatrixSum(const vector<vector<int>>& matrix) {
         return int64_t();
}

void TestCalculateMatrixSum() {
    const vector<vector<int>> matrix = {
      {1, 2, 3, 4},
      {5, 6, 7, 8},
      {9, 10, 11, 12},
      {13, 14, 15, 16}
    };
    ASSERT_EQUAL(CalculateMatrixSum(matrix), 136);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestCalculateMatrixSum);
}
