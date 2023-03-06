// Перебор перестановок
// Дано целое положительное число N, не превышающее 9. 
// Выведите все перестановки чисел от 1 до N 
// в обратном лексикографическом порядке (см. пример).

// Пример
// Ввод
// 3

// Вывод
// 3 2 1
// 3 1 2
// 2 3 1
// 2 1 3
// 1 3 2
// 1 2 3

// Подсказка
// Библиотека <algorithm> содержит готовые функции, позволяющие решить эту задачу.

#include <algorithm>
#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

int main() {

    int N;
    cin >> N;

    vector<int> permutations(N);

    iota(rbegin(permutations), rend(permutations), 1);

    bool not_end_flag = true;
    while (not_end_flag) {

        bool first = true;
        for (auto item : permutations) {
            if (!first) cout << ' ';
            cout << item;
            first = false;
        }
        not_end_flag = prev_permutation(begin(permutations), end(permutations));
        cout << endl;
    };
    return 0;
}