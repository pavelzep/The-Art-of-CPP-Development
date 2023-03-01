// Напишите функцию PrintVectorPart, принимающую вектор целых чисел numbers, 
// выполняющую поиск первого отрицательного числа в нём и выводящую в стандартный вывод все числа, 
// расположенные левее найденного, в обратном порядке.
// Если вектор не содержит отрицательных чисел, выведите все числа в обратном порядке.

#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;


void PrintVectorPart(const vector<int>& numbers);

void PrintVectorPart(const vector<int>& numbers) {
    auto it = find_if(numbers.begin(), numbers.end(), [](int a) {return a < 0;});
    bool first = true;
    while (it != numbers.begin()) {
        --it;

        if (!first)  cout << ' ';
        first = false;
        cout << *it;
    }
}



int main() {
    PrintVectorPart({ 6, 1, 8, -5, 4 });
    cout << endl;
    PrintVectorPart({ -6, 1, 8, -5, 4 });  // ничего не выведется
    cout << endl;
    PrintVectorPart({ 6, 1, 8, 5, 4 });
    cout << endl;
    return 0;
}