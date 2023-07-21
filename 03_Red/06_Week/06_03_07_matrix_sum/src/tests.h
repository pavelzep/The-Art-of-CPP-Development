#pragma once

#include "test_runner.h"
#include <vector>

using namespace std;

void TestCalculateMatrixSum() {
    const vector<vector<int>> matrix = {
      {1, 2, 3, 4},
      {5, 6, 7, 8},
      {9, 10, 11, 12},
      {13, 14, 15, 16}
    };
    ASSERT_EQUAL(CalculateMatrixSum(matrix), 136);
}