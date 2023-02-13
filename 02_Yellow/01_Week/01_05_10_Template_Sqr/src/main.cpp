#include <map>
#include <vector>
#include <utility>
#include <iostream>

using namespace std;

template<typename T> T Sqr(T x);
template<typename X, typename Y> pair <X, Y> operator * (const pair <X, Y>& p1, const pair <X, Y>& p2);
template<typename X> vector <X> operator * (const vector <X>& p1, const vector <X>& p2);
template<typename X, typename Y> map <X, Y> operator *(const map <X, Y>& p1, const map <X, Y>& p2);


template <typename T>
T Sqr(T x) {
    return x * x;
}


template<typename X, typename Y> pair <X, Y> operator * (const pair <X, Y>& p1, const pair <X, Y>& p2) {
    return { p1.first * p2.first, p1.second * p2.second };
}

template<typename X> vector <X> operator * (const vector <X>& v1, const vector <X>& v2) {
    vector<X> rez;
    for (size_t i = 0; i < v1.size(); i++) {
        rez.push_back(v1[i] * v2[i]);
    }
    return rez;
}
template<typename X, typename Y> map <X, Y> operator *(const map <X, Y>& m1, const map <X, Y>& m2) {
    map<X, Y> rez = m1;
    for (auto& item : rez) {
        rez[item.first] = item.second * item.second;
    }
    return rez;
}

int main() {
    vector<int> v = { 1, 2, 3 };
    cout << "vector:";
    for (int x : Sqr(v)) {
        cout << ' ' << x;
    }
    cout << endl;

    map<int, pair<int, int>> map_of_pairs = {
      {4, {2, 2}},
      {7, {4, 3}}
    };
    cout << "map of pairs:" << endl;
    for (const auto& x : Sqr(map_of_pairs)) {
        cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
    }
    return 0;
}