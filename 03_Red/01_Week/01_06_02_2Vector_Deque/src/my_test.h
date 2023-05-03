#include "test_runner.h"
#include "deque.h"

void test_1() {
    Deque<int> t;
    ASSERT_EQUAL(t.Size(), 0u);
}
void test_2() {
    Deque<int> t;
    t.PushBack(42);
    ASSERT_EQUAL(t.Size(), 1u);
    ASSERT_EQUAL(t.Back(), 42);
}
void test_3() {
    Deque<int> t;
    t.PushBack(42);
    ASSERT_EQUAL(t.Size(), 1u);
    ASSERT_EQUAL(t.Front(), 42);
}
void test_4() {
    Deque<int> t;
    t.PushBack(42);
    t.PushBack(43);
    t.PushBack(44);
    t.PushBack(45);

    ASSERT_EQUAL(t.Size(), 4u);
    ASSERT_EQUAL(t[0], 42);
    ASSERT_EQUAL(t[1], 43);
    ASSERT_EQUAL(t[2], 44);
    ASSERT_EQUAL(t[3], 45);
}
void test_5() {
    Deque<int> t;
    t.PushFront(42);
    t.PushFront(43);
    t.PushFront(44);
    t.PushFront(45);

    ASSERT_EQUAL(t.Size(), 4u);
    ASSERT_EQUAL(t[3], 42);
    ASSERT_EQUAL(t[2], 43);
    ASSERT_EQUAL(t[1], 44);
    ASSERT_EQUAL(t[0], 45);
}
void test_6() {
    Deque<int> t;

    t.PushFront(42);
    t.PushFront(43);
    t.PushFront(44);
    t.PushFront(45);
    t.PushBack(41);
    t.PushBack(40);
    t.PushBack(39);
    t.PushBack(38);

    ASSERT_EQUAL(t.Size(), 8u);
    ASSERT_EQUAL(t[7], 38);
    ASSERT_EQUAL(t[6], 39);
    ASSERT_EQUAL(t[5], 40);
    ASSERT_EQUAL(t[4], 41);
    ASSERT_EQUAL(t[3], 42);
    ASSERT_EQUAL(t[2], 43);
    ASSERT_EQUAL(t[1], 44);
    ASSERT_EQUAL(t[0], 45);

    t[2] = 65;
    t[3] = 66;
    t[4] = 67;
    t[5] = 68;

    ASSERT_EQUAL(t[2], 65);
    ASSERT_EQUAL(t[3], 66);
    ASSERT_EQUAL(t[4], 67);
    ASSERT_EQUAL(t[5], 68);
}
void test_7() {
    Deque<int> t;
    t.PushFront(9);
    ASSERT_EQUAL(t[0], 9);
    t.Front() = 8;
    ASSERT_EQUAL(t[0], 8);
    ASSERT_EQUAL(t.At(0), 8);
    t.Back() = 7;
    ASSERT_EQUAL(t[0], 7);
    ASSERT_EQUAL(t.At(0), 7);

}

void MyTest() {
    test_1();
    test_2();
    test_3();
    test_4();
    test_5();
    test_6();
    test_7();
}

void test_8() {
    Deque<int> t;
    try {
        cout << t.At(0);
    }
    catch (std::out_of_range&) {
        cout << "out_of_range" << endl;
    }

}
void test_9() {
    Deque<int> t;
    t.PushBack(1);
    t.PushFront(2);
    try {
        cout << t.At(3);
    }
    catch (std::out_of_range&) {
        cout << "out_of_range" << endl;
    }
}