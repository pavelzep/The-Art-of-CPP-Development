#include "test_runner.h"

using namespace std;

template<typename T>
class Table {
public:
    Table(const size_t row_, const size_t column_):row(0u), column(0u) {
        store.resize(row_);
        if (row_ && column_) {
            for (auto& row : store) {
                row.resize(column_);
            }
            row = row_;
            column = column_;
        }
    };

    void Resize(const size_t row_, const size_t column_) {
        store.resize(row_);
        if (row_ && column_) {
            for (auto& row : store) {
                row.resize(column_);
            }
            row = row_;
            column = column_;
        }
    };

    pair< size_t, size_t >Size() const {
        return make_pair(row, column);
    };

    vector<T>& operator[](size_t index) {
        return store[index];
    };

    const vector<T>& operator[](size_t index) const {
        return store[index];
    };



private:
    vector<vector<T>> store;
    size_t row, column;
};



void TestTable() {
    Table<int> t(1, 1);
    ASSERT_EQUAL(t.Size().first, 1u);
    ASSERT_EQUAL(t.Size().second, 1u);
    t[0][0] = 42;
    ASSERT_EQUAL(t[0][0], 42);
    t.Resize(3, 4);
    ASSERT_EQUAL(t.Size().first, 3u);
    ASSERT_EQUAL(t.Size().second, 4u);
}

void MyTest() {
    {
        Table<int> t(5, 5);
        t[4][4] = 42;
        ASSERT_EQUAL(t[4][4], 42);
        t.Resize(7, 7);
        ASSERT_EQUAL(t[4][4], 42);
        t[3][3] = 55;
        t.Resize(5, 5);
        ASSERT_EQUAL(t[4][4], 42);
        t.Resize(4, 4);
        ASSERT_EQUAL(t[3][3], 55);
    }
}
void MyTest2() {
    {
        Table<int> t(0, 2);
        ASSERT_EQUAL(t.Size().first, 0u);
        ASSERT_EQUAL(t.Size().second, 0u);
    }
    {
        Table<int> t(2, 0);
        ASSERT_EQUAL(t.Size().first, 0u);
        ASSERT_EQUAL(t.Size().second, 0u);
    }
    {
        Table<int> t(0, 0);
        ASSERT_EQUAL(t.Size().first, 0u);
        ASSERT_EQUAL(t.Size().second, 0u);
    }
}
int main() {
    TestRunner tr;
    RUN_TEST(tr, TestTable);
    RUN_TEST(tr, MyTest);
    RUN_TEST(tr, MyTest2);

    return 0;
}
