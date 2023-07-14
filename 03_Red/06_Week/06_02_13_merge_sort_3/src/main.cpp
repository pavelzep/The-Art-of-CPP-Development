#include "test_runner.h"
#include <algorithm>
#include <memory>
#include <vector>
#include <iterator>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    // Напишите реализацию функции,
    // не копируя сортируемые элементы

    if ((range_end - range_begin) < 2) return;
    vector<typename RandomIt::value_type> elements(make_move_iterator(range_begin), make_move_iterator(range_end));
    auto it12 = elements.begin() + (elements.end() - elements.begin()) / 3;
    auto it23 = it12 + (elements.end() - elements.begin()) / 3;
    MergeSort(elements.begin(), it12);
    MergeSort(it12, it23);
    MergeSort(it23, elements.end());
    vector<typename RandomIt::value_type> temp_vect;
    merge(make_move_iterator(elements.begin()), make_move_iterator(it12),
        make_move_iterator(it12), make_move_iterator(it23),
        back_inserter(temp_vect));
    merge(make_move_iterator(temp_vect.begin()), make_move_iterator(temp_vect.end()),
        make_move_iterator(it23), make_move_iterator(elements.end()),
        range_begin);
}

void TestIntVector() {
    vector<int> numbers = { 6, 1, 3, 9, 1, 9, 8, 12, 1 };
    MergeSort(begin(numbers), end(numbers));
    ASSERT(is_sorted(begin(numbers), end(numbers)));
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestIntVector);
    return 0;
}
