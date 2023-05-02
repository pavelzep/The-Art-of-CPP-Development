#include "test_runner.h"
#include <vector>

using namespace std;

template<typename T>
class Deque {
public:

    Deque() {

    }

    bool Empty() const {
        return (front.empty() && back.empty());
    }
    size_t Size() const {
        return front.size() + back.size();
    }

    T& At(size_t index) {

    }

    const T& At(size_t index) const {

    }

    T& operator[](size_t index) {

    }

    const T& operator[](size_t index) const {

    }

    T& Front() {
        return front.back();
    }

    const T& Front() const {
        return front.back();
    }

    T& Back() {
        return back.back();
    }

    const T& Back() const {
        return back.back();
    }

    void PushFront(const T& t) {
        front.push_back(t);
    }

    void PushBack(const T& t) {
        back.push_back(t);
    }


private:

    vector<T> front;
    vector<T> back;

};






void MyTest() {
    {
        Deque<int> t;
        ASSERT_EQUAL(t.Size(), 0u);
    }

    {
        Deque<int> t;
        t.PushBack(42);
        ASSERT_EQUAL(t.Size(), 1u);
        ASSERT_EQUAL(t.Back(), 42);
    }
    {
        Deque<int> t;
        t.PushBack(42);
        ASSERT_EQUAL(t.Size(), 1u);
        ASSERT_EQUAL(t.Front(), 42);
    }
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, MyTest);


    return 0;
}
