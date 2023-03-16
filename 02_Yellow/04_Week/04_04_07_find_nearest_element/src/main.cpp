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
#include <algorithm>
#include <iostream>



using namespace std;

set<int>::const_iterator FindNearestElement(const set<int>& numbers, int border);

set<int>::const_iterator FindNearestElement(const set<int>& numbers, int border) {

    //сначала найдем первый не меньше чем бордер
    //то есть тот что первым справа от него или его самого
    auto right = numbers.lower_bound(border);

    //если найденный элемент равен началу то его и вернем
    if (right == numbers.begin()) return numbers.begin();

    //найдем первый элемент меньше чем бордер, это и будет предыдушщий 
    //от предыдущего найденного, то есть первый слева
    auto left = prev(right);

    //если первый не меньший чем бордер оказался правее чем конец хранилища,
    //то вернем предыдущий от него, то есть тот что первый не меньший чем бордер

    if (right == numbers.end()) return left;

    // посчитаем какой ближе к бордер, тот и вернем.
    if (border - *right <= *left - border)
        return left;
    else
        return right;

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