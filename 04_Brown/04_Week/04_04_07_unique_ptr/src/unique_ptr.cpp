#include "test_runner.h"

#include <cstddef>  // нужно для nullptr_t

using namespace std;

// Реализуйте шаблон класса UniquePtr
template <typename T>
class UniquePtr {
private:
    T* ptr_;
public:
    UniquePtr() { ptr_ = nullptr; }
    UniquePtr(T* ptr) :ptr_(ptr) {}
    UniquePtr(const UniquePtr&) = delete;
    UniquePtr(UniquePtr&& other) {
        this->ptr_ = other.ptr_;
    }
    UniquePtr& operator = (const UniquePtr&) = delete;
    UniquePtr& operator = (nullptr_t) {

    }
    UniquePtr& operator = (UniquePtr&& other) {

    }
    ~UniquePtr() {
        delete ptr_;
        ptr_ = nullptr;
    }

    T& operator * () const { return *ptr_; }
    T* operator -> () const { return ptr_; }
    T* Release() {}
    void Reset(T* ptr) {}
    void Swap(UniquePtr& other) {}
    T* Get() const { return ptr_; }
};


struct Item {
    static int counter;
    int value;
    Item(int v = 0) : value(v) {
        ++counter;
    }
    Item(const Item& other) : value(other.value) {
        ++counter;
    }
    ~Item() {
        --counter;
    }
};

int Item::counter = 0;


void TestLifetime() {
    Item::counter = 0;
    {
        UniquePtr<Item> ptr(new Item);
        ASSERT_EQUAL(Item::counter, 1);

        ptr.Reset(new Item);
        ASSERT_EQUAL(Item::counter, 1);
    }
    ASSERT_EQUAL(Item::counter, 0);

    {
        UniquePtr<Item> ptr(new Item);
        ASSERT_EQUAL(Item::counter, 1);

        auto rawPtr = ptr.Release();
        ASSERT_EQUAL(Item::counter, 1);

        delete rawPtr;
        ASSERT_EQUAL(Item::counter, 0);
    }
    ASSERT_EQUAL(Item::counter, 0);
}

void TestGetters() {
    UniquePtr<Item> ptr(new Item(42));
    ASSERT_EQUAL(ptr.Get()->value, 42);
    ASSERT_EQUAL((*ptr).value, 42);
    ASSERT_EQUAL(ptr->value, 42);
}

struct Test {
    int a;
    int b;
    int c;
};

void MyTest() {
    Test t{ 1,2,4 };
    UniquePtr<Test> pTest(&t);
    // auto x = pTest.Get();
    // auto y = pTest->a;
    // auto z = *pTest;


    return;
}

int* m() {
    TestRunner tr;
    // RUN_TEST(tr, TestLifetime);
    // RUN_TEST(tr, TestGetters);
    RUN_TEST(tr, MyTest);

}
