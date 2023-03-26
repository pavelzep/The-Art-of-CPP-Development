//  Часть 2. Группировка по префиксу
// Напишите более универсальный вариант функции FindStartsWith, принимающий 
// в качестве префикса произвольную строку, состоящую из строчных латинских букв.
// template <typename RandomIt>
// pair<RandomIt, RandomIt> FindStartsWith(
//     RandomIt range_begin, RandomIt range_end,
//     const string& prefix);
// Пример кода
// int main() {
//     const vector<string> sorted_strings = { "moscow", "motovilikha", "murmansk" };
//     const auto mo_result =
//         FindStartsWith(begin(sorted_strings), end(sorted_strings), "mo");
//     for (auto it = mo_result.first; it != mo_result.second; ++it) {
//         cout << *it << " ";
//     }
//     cout << endl;
//     const auto mt_result =
//         FindStartsWith(begin(sorted_strings), end(sorted_strings), "mt");
//     cout << (mt_result.first - begin(sorted_strings)) << " " <<
//         (mt_result.second - begin(sorted_strings)) << endl;
//     const auto na_result =
//         FindStartsWith(begin(sorted_strings), end(sorted_strings), "na");
//     cout << (na_result.first - begin(sorted_strings)) << " " <<
//         (na_result.second - begin(sorted_strings)) << endl;
//     return 0;
// }
// Вывод
// moscow motovilikha
// 2 2
// 3 3



#include <vector>
#include <string>
#include <iostream>
#include <utility>
#include <algorithm>

using namespace std;

template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin, RandomIt range_end, const string& prefix);


template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin, RandomIt range_end, const string& prefix) {

    auto low = lower_bound(range_begin, range_end, prefix);
    string pref_ = prefix;
    pref_[pref_.size() - 1]++;
    auto up = lower_bound(range_begin, range_end, pref_);
    return { low, up };


    // return equal_range(range_begin, range_end, prefix, [](const string& s, const string& v) {

    //     return s < v;
    //     });

}

int main() {
    const vector<string> sorted_strings = { "moscow", "motovilikha", "murmansk" };
    const auto mo_result =
        FindStartsWith(begin(sorted_strings), end(sorted_strings), "mo");
    for (auto it = mo_result.first; it != mo_result.second; ++it) {
        cout << *it << " ";
    }
    cout << endl;
    const auto mt_result =
        FindStartsWith(begin(sorted_strings), end(sorted_strings), "mt");
    cout << (mt_result.first - begin(sorted_strings)) << " " <<
        (mt_result.second - begin(sorted_strings)) << endl;
    const auto na_result =
        FindStartsWith(begin(sorted_strings), end(sorted_strings), "na");
    cout << (na_result.first - begin(sorted_strings)) << " " <<
        (na_result.second - begin(sorted_strings)) << endl;
    return 0;
}