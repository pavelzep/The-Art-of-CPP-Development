#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>
using namespace std;

template <class T>
class ObjectPool {
public:
    T* Allocate();
    T* TryAllocate();

    void Deallocate(T* object);

    ~ObjectPool();

private:
    // Добавьте сюда поля
    deque<T*> alloc_objects;
    deque<T*> dealloc_objects;
};

void TestObjectPool() {
    ObjectPool<string> pool;

    auto p1 = pool.Allocate();
    auto p2 = pool.Allocate();
    auto p3 = pool.Allocate();

    *p1 = "first";
    *p2 = "second";
    *p3 = "third";

    pool.Deallocate(p2);
    ASSERT_EQUAL(*pool.Allocate(), "second");

    pool.Deallocate(p3);
    pool.Deallocate(p1);
    ASSERT_EQUAL(*pool.Allocate(), "third");
    ASSERT_EQUAL(*pool.Allocate(), "first");

    pool.Deallocate(p1);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestObjectPool);
    return 0;
}

template<class T>
T* ObjectPool<T>::Allocate() {

    if (!dealloc_objects.empty()) {
        auto obj = dealloc_objects.front();
        alloc_objects.push_back(obj);
        dealloc_objects.pop_front();
        return obj;
    } else {

        auto obj_ = new T();
        alloc_objects.push_back(obj_);
        return obj_;
    }
}

template<class T>
T* ObjectPool<T>::TryAllocate() {
    if (!dealloc_objects.empty()) {
        auto obj = dealloc_objects.front();
        alloc_objects.push_back(obj);
        dealloc_objects.pop_front();
        return obj;
    } else {
        return nullptr;
    }

}

template<class T>
void ObjectPool<T>::Deallocate(T* object) {
    auto it = find(alloc_objects.begin(), alloc_objects.end(), object);
    if (it == alloc_objects.end()) throw invalid_argument("");
    dealloc_objects.push_back(object);
    alloc_objects.erase(it);

}

template<class T>
ObjectPool<T>::~ObjectPool() {

    while (!alloc_objects.empty()) {
        auto obj = alloc_objects.front();
        alloc_objects.pop_front();
        delete obj;
    }

    while (!dealloc_objects.empty()) {
        auto obj = dealloc_objects.front();
        dealloc_objects.pop_front();
        delete obj;
    }
}
