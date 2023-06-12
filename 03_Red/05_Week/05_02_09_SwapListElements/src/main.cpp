
#include <list>
#include <iterator>
#include <iostream>

using namespace std;
template <typename T>
void SwapListElements(list<T>& lst, typename list<T>::iterator iterator1, typename list<T>::iterator iterator2) {
    const auto iterator2_next = next(iterator2);
    lst.splice(iterator1, lst, iterator2);
    lst.splice(iterator2_next, lst, iterator1);
};

template <typename T>
ostream& operator << (ostream& out, const list<T>& lst) {
    for (const auto& item : lst) out << item << ' ';
    return out;
}



int main() {

    std::list<int> list{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    auto it1 = list.begin();
    advance(it1, 4);

    auto it2 = list.begin();
    advance(it2, 7);

    SwapListElements(list, it1, it2);
    cout << list << endl;

    return 0;
}