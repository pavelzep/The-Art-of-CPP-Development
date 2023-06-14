
#include "simple_list.h"


int main() {

    SimpleList<int> lst;
    for (int i = 0;i < 10;++i) {
        lst.PushBack(i);
    }

    lst.Print();

    return 0;
}


