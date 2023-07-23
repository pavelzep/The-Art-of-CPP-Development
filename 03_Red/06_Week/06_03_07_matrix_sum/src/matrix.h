#pragma once

#include "paginator.h"

#include <numeric>
#include <future>

#define THREAD_COUNT 4

using namespace std;

template <typename ContainerOfVectors >
int64_t SumSingleThread(const ContainerOfVectors& matrix) {
    int64_t result = 0;
    for (auto row : matrix) {
        result = accumulate(row.begin(), row.end(), result);
    }
    return result;
}

int64_t CalculateMatrixSum(const vector<vector<int>>& matrix) {
    int64_t result = 0;
    vector <future <int64_t >> futures;
    size_t page_size = matrix.size() / THREAD_COUNT;
  
    auto P = Paginate(matrix, page_size);
    for (const auto& page : P) {
        futures.push_back(
            async([&page,  &result] {return SumSingleThread(page );})
        );
    }
    
    for (auto &item : futures) {
        result += item.get();
    }
    return result;
}

template <typename ContainerOfVectors >
void GenerateSingleThread(ContainerOfVectors& result, size_t first_row, size_t column_size) {
    for (auto& row : result) {
        row.reserve(column_size);
        for (size_t column = 0; column < column_size; ++column) {
            row.push_back(first_row ^ column);
        }
        ++first_row;
    }
}

vector <vector <int>> GenerateSingleThread(size_t size) {
    vector <vector <int>> result(size);
    GenerateSingleThread(result, 0, size);
    return result;
}

vector <vector <int>> GenerateMultiThread(size_t size, size_t page_size) {
    vector <vector <int>> result(size);
    vector <future <void >> futures;
    size_t first_row = 0;
    for (auto page : Paginate(result, page_size)) {
        futures.push_back(
            async([page, first_row, size] {
                GenerateSingleThread(page, first_row, size);
                })
        );
        first_row += page_size;
    }
    return result;
}