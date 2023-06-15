

#pragma once
#include <iostream>
#include <iterator>

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

    Node* Head() { return head; }
    Node* Next(Node* it) { return it->next; }
    Node* Prev(Node* it) { return it->prev; }

    ~SimpleList();
    void PushBack(const T& value);
    void Print();
    void Splice(Node* pos, SimpleList& other, Node* first, Node* last);
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

template<typename T>
inline void SimpleList<T>::Splice(Node* pos, SimpleList& other, Node* first, Node* last) {
    // pos->prev->next = first; 
    // pos->prev = last->prev;
    // first->prev = pos->prev;
    // last->prev->next = pos;
    // first->prev->next = last;
    // last->prev = first->prev;

    auto temp = pos->prev;
    pos->prev->next = first;    //1
    first->prev->next = last; //5
    last->prev->next = pos; //4
    pos->prev = last->prev; //2
    last->prev = first->prev; //6
    first->prev = temp; //3

}




