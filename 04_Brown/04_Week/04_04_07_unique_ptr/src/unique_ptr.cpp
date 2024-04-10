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
    UniquePtr& operator = (const UniquePtr&) = delete;

    UniquePtr(UniquePtr&& other) {
        if (this != &other) {
            //  delete this->ptr_;
            this->ptr_ = other.ptr_;
            other.ptr_ = nullptr;
        }
    }
    UniquePtr& operator = (nullptr_t) {
        if (ptr_ != nullptr) {
            delete ptr_;
            ptr_ = nullptr;
        }return *this;
    }
    UniquePtr& operator = (UniquePtr&& other) {
        if (this != &other) {
            delete this->ptr_;
            this->ptr_ = other.ptr_;
            other.ptr_ = nullptr;
        }
        return *this;
    }

    ~UniquePtr() {
        if (ptr_ != nullptr) {
            delete ptr_;
            ptr_ = nullptr;
        }
    }
    T& operator * () const { return *ptr_; }
    T* operator -> () const { return ptr_; }
    T* Release() {
        auto result = ptr_;
        ptr_ = nullptr;
        return result;
    }
    void Reset(T* ptr) {
        if (ptr_ != nullptr) {
            delete ptr_;
        }
        ptr_ = ptr;
    }
    void Swap(UniquePtr& other) {
        auto temp = other.ptr_;
        other.ptr_ = this->ptr_;
        this->ptr_ = temp;
    }
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
void TestMove() {
    {
        auto a = UniquePtr(new Item(42));
        auto b = UniquePtr(move(a));
    }
    {
        auto a = UniquePtr(new Item(42));
        a = UniquePtr(move(a));
    }
    {
        auto a = UniquePtr(new Item(42));
        a = UniquePtr(move(a));
    }
}

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

void TestOneDelete() {
    {
        {
            UniquePtr<Item> ptr1(new Item(42));
            UniquePtr<Item> ptr2 = move(ptr1);
        }
    }
    {
        {
            auto a = UniquePtr(new Item(42));
            auto b = std::move(a);
        }
        ASSERT_EQUAL(Item::counter, 0);
    }
    {
        {
            auto a = UniquePtr(new Item(42));
            auto b = UniquePtr(std::move(a));
        }
        ASSERT_EQUAL(Item::counter, 0);
    }
}

void TestNullptr() {
    {
        auto a = UniquePtr<int>(nullptr);
        a.Reset(nullptr);
    }
    {
        auto a = UniquePtr(new Item(42));
        a.Reset(nullptr);
    }
    {
        auto a = UniquePtr<int>();
    }
    {
        auto a = UniquePtr<int>();
        a.Reset(nullptr);
    }
    {
        auto a = (int*)nullptr;
        delete a;
    }
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestLifetime);
    RUN_TEST(tr, TestGetters);
    RUN_TEST(tr, TestOneDelete);
    RUN_TEST(tr, TestNullptr);
    return 0;
}