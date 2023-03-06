// Сортировка слиянием
// Напишите шаблонную функцию MergeSort, принимающую два итератора шаблонного типа RandomIt и 
// сортирующую заданный ими диапазон с помощью сортировки слиянием. Гарантируется, что:
// итераторы типа RandomIt аналогичны по функциональности итераторам вектора и строки, то есть 
// их можно сравнивать с помощью операторов <, <=, > и >=, а также вычитать и складывать с числами;
// сортируемые объекты можно сравнивать с помощью оператора <.
// template <typename RandomIt>
// void MergeSort(RandomIt range_begin, RandomIt range_end);

// Часть 1. Реализация с разбиением на 2 части
// Алгоритм
// Классический алгоритм сортировки слиянием выглядит следующим образом:
// Если диапазон содержит меньше 2 элементов, выйти из функции.
// Создать вектор, содержащий все элементы текущего диапазона.
// Разбить вектор на две равные части. (В этой задаче гарантируется, что длина передаваемого 
// диапазона является степенью двойки, так что вектор всегда можно разбить на две равные части.)
// Вызвать функцию MergeSort от каждой половины вектора.
// С помощью алгоритма merge слить отсортированные половины, записав полученный отсортированный 
// диапазон вместо исходного.

// Вы должны реализовать именно этот алгоритм и никакой другой: тестирующая система будет проверять, 
// что вы выполняете с элементами именно эти действия.

// Подсказка:
// Чтобы создать вектор, содержащий все элементы текущего диапазона (п. 2 алгоритма), необходимо 
// уметь по типу итератора узнавать тип элементов, на которые он указывает. Если итератор RandomIt 
// принадлежит стандартному контейнеру (вектору, строке, множеству, словарю...), нижележащий тип 
// можно получить с помощью выражения typename RandomIt::value_type. Таким образом, гарантируется, 
// что создать вектор в п. 2 можно следующим образом:
// vector<typename RandomIt::value_type> elements(range_begin, range_end);

// Пример кода:

// int main() {
//   vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1};
//   MergeSort(begin(v), end(v));
//   for (int x : v) {
//     cout << x << " ";
//   }
//   cout << endl;
//   return 0;
// }

// Вывод:
// 0 1 4 4 4 6 6 7

#include <vector>
#include <iostream>
#include <algorithm>
//#include <iterator>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end);

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    if ((range_end - range_begin) < 2) return;
    vector<typename RandomIt::value_type> elements(range_begin, range_end);
    auto it = elements.begin() + (elements.end() - elements.begin()) / 2;
    // vector<typename RandomIt::value_type> v1(elements.begin(), it);
    // vector<typename RandomIt::value_type> v2(it, elements.end());
    // MergeSort(v1.begin(), v1.end());
    // MergeSort(v2.begin(), v2.end());
    MergeSort(elements.begin(), it);
    MergeSort(it, elements.end());

    merge(elements.begin(), it, it, elements.end(), range_begin);
}


int main() {
    vector<int> v = { 6, 4, 7, 6, 4, 4, 0, 1 };
    //vector<int> v = {1};
    MergeSort(begin(v), end(v));
    for (int x : v) {
        cout << x << " ";
    }
    cout << endl;
    return 0;
}


