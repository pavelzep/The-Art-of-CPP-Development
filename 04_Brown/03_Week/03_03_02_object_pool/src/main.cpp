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
    T* Allocate() {
        T* t = TryAllocate();
        if (!t)
            t = new T();
        alloc_pool.insert(t);
        return t;
    }

    T* TryAllocate() {
        T* t = nullptr;
        if (!dealloc_pool.empty()) {
            t = dealloc_pool.front();
            dealloc_pool.pop();
            alloc_pool.insert(t);
        }
        return t;
    }

    void Deallocate(T* object) {
        if (alloc_pool.find(object) == alloc_pool.end()) {
            throw invalid_argument("");
        }
        alloc_pool.erase(object);
        dealloc_pool.push(object);
    }

    ~ObjectPool() {
        for (auto obj : alloc_pool) {
            delete obj;
        }
        while (!dealloc_pool.empty()) {
            auto t = dealloc_pool.front();
            dealloc_pool.pop();
            delete t;
        }
    }

private:
    set<T*> alloc_pool;
    queue<T*> dealloc_pool;


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
