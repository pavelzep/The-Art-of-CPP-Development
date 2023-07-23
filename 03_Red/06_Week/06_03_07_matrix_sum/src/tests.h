#pragma once

#include "test_runner.h"
#include "profile.h"
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

void EmptyTest() {
    const vector<vector<int>> matrix = { {} };
    ASSERT_EQUAL(CalculateMatrixSum(matrix), 0);
}

void OneTest() {
    const vector<vector<int>> matrix = { {1} };
    ASSERT_EQUAL(CalculateMatrixSum(matrix), 1);
}
void SingleThread_Test() {
    size_t matrix_size = 7000;
    const vector<vector<int>> matrix = GenerateMultiThread(matrix_size, 1750);
    ASSERT_EQUAL(SumSingleThread(matrix), 195928050144);
}
void MultiThread_Test() {
    size_t matrix_size = 7000;
    const vector<vector<int>> matrix = GenerateMultiThread(matrix_size, 1750);
    ASSERT_EQUAL(CalculateMatrixSum(matrix), 195928050144);
}

void TestAll() {
    TestRunner tr;
    {
        LOG_DURATION("TestCalculateMatrixSum");
        RUN_TEST(tr, TestCalculateMatrixSum);
    }
    {
        LOG_DURATION("EmptyTest");
        RUN_TEST(tr, EmptyTest);
    }
    {
        LOG_DURATION("OneTest");
        RUN_TEST(tr, OneTest);
    }
    {
        LOG_DURATION("SingleThread_Test");
        RUN_TEST(tr, SingleThread_Test);
    }
    {
        LOG_DURATION("MultiThread_Test");
        RUN_TEST(tr, MultiThread_Test);
    }


};