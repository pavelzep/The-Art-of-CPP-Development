// Дана функция f, принимающая число и возвращающая true, если для него выполнено некоторое условие, 
// и false в противном случае. Кроме того, дано множество чисел s и пустой вектор v:
// 
// Отметьте отрывки кода, которые заполнят вектор v всеми элементами множества s, не удовлетворяющими условию f.

#include <set>
#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>

using namespace std;

bool f(int x) {
    return x > 4;
}

template <typename element_type>
void print(vector<element_type>& v) {
    auto it = v.begin();
    while (it != v.end()) {
        cout << *it << ' ';
        ++it;
    }
    cout << endl;
}


int main() {
    set<int> s = { 0,1,2,3,4,5,6,7,8,9 };

    //1 ok
    {

        vector<int> v;
        cout << 1 << ": ";
        remove_copy_if(begin(s), end(s), back_inserter(v), f);
        print(v);
    }

    //2 no
    {
        vector<int> v;
        cout << 2 << ": ";
        remove_copy_if(begin(s), end(s), back_inserter(v), [](int x) { return !f(x); });
        print(v);
    }

    //3 no
    {
        vector<int> v;
        cout << 3 << ": ";
        copy_if(begin(s), end(s), back_inserter(v), f);
        print(v);
    }

    //4 ok
    {
        vector<int> v;
        cout << 4 << ": ";
        copy_if(begin(s), end(s), back_inserter(v), [](int x) { return !f(x); });
        print(v);
    }

    // //5 no
    // {
    //     vector<int> v;
    //     cout << 5 << ": ";
    //     auto it = partition(begin(s), end(s), f);
    //     copy(it, end(s), back_inserter(v));
    //     print(v);
    // }

    // //6 no
    // {
    //     vector<int> v;
    //     cout << 6 << ": ";
    //     auto it = remove_if(begin(s), end(s), [](int x) { return !f(x); });
    //     copy(it, end(s), back_inserter(v));
    //     print(v);
    // }

    //7 no
    {
        vector<int> v;
        cout << 7 << ": ";
        v.assign(begin(s), end(s));
        auto it = partition(begin(v), end(v), f);
        v.erase(it, end(v));
        print(v);
    }

    //8 ok
    {
        vector<int> v;
        cout << 8 << ": ";
        v.assign(begin(s), end(s));
        auto it = partition(begin(v), end(v), f);
        v.erase(begin(v), it);
        print(v);
    }

    //9 no
    {
        vector<int> v;
        cout << 9 << ": ";
        v.assign(begin(s), end(s));
        auto it = remove_if(begin(v), end(v), [](int x) { return !f(x); });
        v.erase(it, end(v));
        print(v);
    }

    //10 ok
    {
        vector<int> v;
        cout << 10 << ": ";
        v.assign(begin(s), end(s));
        auto it = remove_if(begin(v), end(v), f);
        v.erase(it, end(v));
        print(v);
    }

    //11 no
    {
        vector<int> v;
        cout << 11 << ": ";
        vector<int> garbage;
        partition_copy(begin(s), end(s), back_inserter(v), back_inserter(garbage), f);
        print(v);
    }

    //12 ok
    {
        vector<int> v;
        cout << 12 << ": ";
        vector<int> garbage;
        partition_copy(begin(s), end(s), back_inserter(garbage), back_inserter(v), f);
        print(v);
    }

    //13 no
    {
        vector<int> v;
        cout << 13 << ": ";
        v.assign(begin(s), end(s));
        sort(begin(v), end(v), [](int lhs, int rhs) { return f(lhs) > f(rhs); });
        auto it = partition_point(begin(v), end(v), f);
        v.erase(it, end(v));
        print(v);
    }

    //14 ok
    {
        vector<int> v;
        cout << 14 << ": ";
        v.assign(begin(s), end(s));
        sort(begin(v), end(v), [](int lhs, int rhs) { return f(lhs) > f(rhs); });
        auto it = partition_point(begin(v), end(v), f); v.erase(begin(v), it);
        print(v);
    }

    return 0;
}