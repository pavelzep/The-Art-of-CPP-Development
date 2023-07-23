#include "test_runner.h"
#include "profile.h"

#include "matrix.h"
#include "tests.h"

using namespace std;

int main() {
    // TestRunner tr;
    // RUN_TEST(tr, TestCalculateMatrixSum);


    // LOG_DURATION("Total");
    const size_t matrix_size = 7000;
    vector <vector <int>> matrix;

    // {
    //     LOG_DURATION("Single thread generation");
    //     matrix = GenerateSingleThread(matrix_size);
    // }
    // {
    //     LOG_DURATION("Multi thread generation");
    //     matrix = GenerateMultiThread(matrix_size, 900);
    // }

    matrix = GenerateMultiThread(matrix_size, 900);
    {
        LOG_DURATION("Single thread sum");
        cout << SumSingleThread(matrix) << endl;
    }
    {
        LOG_DURATION("CalculateMatrixSum");
        cout << CalculateMatrixSum(matrix) << endl;
    }


}
