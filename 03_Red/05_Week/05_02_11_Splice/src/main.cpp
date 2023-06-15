
#include "simple_list.h"


int main() {

    SimpleList<int> lst1;
    for (int i = 0;i < 10;++i) lst1.PushBack(i);

    lst1.Print();
    std::cout << std::endl;

    SimpleList<int> lst2;
    for (int i = 10;i < 20;++i) lst2.PushBack(i);

    lst2.Print();
    std::cout << std::endl;

    auto pos = lst2.Head()->next->next->next; //13
    std::cout << pos->value;
    std::cout << std::endl;

    auto first = lst1.Head()->next->next->next;//
    auto last = first->next->next->next;
    std::cout << first->value << ' ' << last->prev->value << std::endl;


    lst2.Splice(pos, lst2, first, last);
    lst1.Print();
    std::cout << std::endl;
    lst2.Print();
    std::cout << std::endl;


    return 0;
}


