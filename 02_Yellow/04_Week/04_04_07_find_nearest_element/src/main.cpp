// Напишите функцию FindNearestElement, для множества 
// целых чисел numbers и данного числа border возвращающую 
// итератор на элемент множества, ближайший к border. 
// Если ближайших элементов несколько,
// верните итератор на наименьший из них.
// Вывод:
// 1 4 4 6 6
// 1
// set<int>::const_iterator —
// тип итераторов для константного множества целых чисел

#include <set>
#include <iostream>
#include <algorithm>
#include <utility>


using namespace std;


set<int>::const_iterator FindNearestElement(const set<int>& numbers, int border);

set<int>::const_iterator FindNearestElement(const set<int>& numbers, int border) {

    auto range = equal_range(begin(numbers), end(numbers), border);


    set<int>::const_iterator result;

    auto it = find(begin(numbers), end(numbers), border);

    //auto a = it - range.first;

    cout << "aaaa: " << min(*prev(range.first), *range.second);

    return result;
}


int main() {
    set<int> numbers = { 1, 4, 6 };
    cout <<
        *FindNearestElement(numbers, 0) << " " <<
        *FindNearestElement(numbers, 3) << " " <<
        *FindNearestElement(numbers, 5) << " " <<
        *FindNearestElement(numbers, 6) << " " <<
        *FindNearestElement(numbers, 100) << endl;

    set<int> empty_set;

    cout << (FindNearestElement(empty_set, 8) == end(empty_set)) << endl;
    return 0;
}