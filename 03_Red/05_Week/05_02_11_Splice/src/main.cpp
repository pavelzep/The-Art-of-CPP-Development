#include <list>

template<typename T>
class MyList {
    struct Node {
        T value;
        Node* prev = nullptr;
        Node* next = nullptr;
    };


    ~MyList();


    void push_back

    Node* head = nullptr;
    Node* tail = nullptr;

private:

};

template<typename T>
MyList<T>::~MyList() {
}

template<typename T>
MyList<T>& operator<<(MyList<T>& lst, const T& value) {
    auto new_tail = new Node{ value };

    if (lst.head == nullptr) {
        lst.head = new_tail;
        lst.tail = new_tail;
    } else {
        lst.tail->next = new_tail;
        new_tail->prev = lst.tail;
        lst.tail = new_tail;
    }
    return lst;
};




int main() {

    MyList<int> lst;
    lst << 1 << 2 << 3 << 4 << 5;

    return 0;
}


