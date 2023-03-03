// Даны итераторы вектора, строки и множества :
// Отметьте вызовы алгоритмов, которые скомпилируются.

#include <set>
#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <numeric>

using namespace std;

int main() {

    vector<int> vec;
    auto vector_begin = begin(vec);
    auto vector_end = end(vec);

    string str;
    auto string_begin = begin(str);
    auto string_end = end(str);

    set<int> s;
    auto set_begin = begin(s);
    auto set_end = end(s);

    { auto res = is_heap(string_begin, string_end);}
    //{ auto res = is_heap(set_begin, set_end);}
    { auto res = is_permutation(vector_begin, vector_end, vector_begin);}
    { auto res = is_permutation(set_begin, set_end, vector_begin);}
    //{ auto res = is_permutation(set_begin, set_end, back_inserter(vec));}
    { auto res = next_permutation(string_begin, string_end);}
    //{ auto res = next_permutation(set_begin, set_end);}
    //{ partial_sum(vector_begin, vector_end, set_begin);}
    {partial_sum(set_begin, set_end, vector_begin);}
    {partial_sum(set_begin, set_end, back_inserter(vec));}
    { auto res = accumulate(vector_begin, vector_end, 0);}
    { auto res = accumulate(set_begin, set_end, 0);}

    return 0;
}