

#pragma once
#include <iostream>

template<typename T>
class SimpleList {
    struct Node {
        T value;
        Node* prev = nullptr;
        Node* next = nullptr;
    };

    Node* head = nullptr;
    Node* tail = nullptr;

public:

    ~SimpleList();
    void PushBack(const T& value);
    void Print();
};

template<typename T>
SimpleList<T>::~SimpleList() {
}

template<typename T>
inline void SimpleList<T>::PushBack(const T& value) {
    auto new_tail = new Node{ value };

    if (head == nullptr) {
        head = new_tail;
        tail = new_tail;
    } else {
        tail->next = new_tail;
        new_tail->prev = tail;
        tail = new_tail;
    }
}

template<typename T>
inline void SimpleList<T>::Print() {
    auto it = head;
    if (!it) return;
    do {
        std::cout << it->value << ' ';
        it = it->next;
    } while (it != nullptr);
}




