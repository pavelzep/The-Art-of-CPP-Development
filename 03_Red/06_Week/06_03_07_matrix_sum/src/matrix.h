#pragma once

// #include "paginator.h"

#include <numeric>
#include <future>
#include <vector>
#define THREAD_COUNT 4

using namespace std;

template<typename Iterator>
class IteratorRange {
private:
    Iterator first, last;
public:
    IteratorRange(Iterator f, Iterator l)
        : first(f)
        , last(l) {
    }
    Iterator begin() const { return first; }
    Iterator end() const { return last; }
    size_t size() const { return end() - begin(); }
};

template <typename Iterator>
class Paginator {
private:
    vector <IteratorRange<Iterator>> pages;
public:
    Paginator(Iterator begin, Iterator end, size_t page_size) {
        for (Iterator it = begin;it < end;it = next(it, page_size)) {
            IteratorRange page(it, min(next(it, page_size), end));
            pages.push_back(page);
        }
    }
    size_t size() const { return pages.size(); }
    auto begin() const { return pages.begin(); }
    auto end() const { return pages.end(); }
};

template <typename Container>
auto Paginate(Container& container, size_t page_size) {
    return Paginator(container.begin(), container.end(), page_size);
};

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

    size_t thread_count = matrix.size() < 4 ? 1 : THREAD_COUNT;
    size_t page_size = matrix.size() / thread_count;

    for (const auto page : Paginate(matrix, page_size)) {
        futures.push_back(
            async([page, &result] {return SumSingleThread(page);})
        );
    }

    for ( auto &item : futures) {
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