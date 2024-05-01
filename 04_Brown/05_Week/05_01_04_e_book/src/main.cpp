#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <vector>

// #define TEST_ON

#ifdef TEST_ON
#include "test_runner.h"

void Test_All();
#endif

using namespace std;

class ReadingManager {
public:
    ReadingManager() :
        user_count(0),
        pages(1000, 0) {

    }

    void Read(int user, int page) {
        auto it = user_to_page.find(user);
        if (it == user_to_page.end()) {
            ++user_count;
            for (int i = 0; i < page; ++i) {
                pages[i]++;
            }
        } else {
            for (int i = user_to_page[user]; i < page;++i) {
                pages[i]++;
            }
        }
        user_to_page[user] = page;
    }

    double Cheer(int user) const {
        auto it = user_to_page.find(user);
        if (it == user_to_page.end()) return {};
        if (user_count == 1) return 1.0;


        return ((user_count - 1) - (pages[it->second - 1] - 1)) * 1.0 / (user_count - 1);

    }

private:
    int user_count;
    map <int, int> user_to_page;
    vector <int> pages;
};

int main() {

#ifdef TEST_ON
    Test_All();
#endif

#ifndef TEST_ON
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ReadingManager manager;

    int query_count;
    cin >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id) {
        string query_type;
        cin >> query_type;
        int user_id;
        cin >> user_id;

        if (query_type == "READ") {
            int page_count;
            cin >> page_count;
            manager.Read(user_id, page_count);
        } else if (query_type == "CHEER") {
            cout << setprecision(6) << manager.Cheer(user_id) << "\n";
        }
    }
    #endif
    return 0;
}

#ifdef TEST_ON
void Test1() {
    ReadingManager manager;
    ASSERT_EQUAL(manager.Cheer(5), 0.0);
    manager.Read(1, 10);
    ASSERT_EQUAL(manager.Cheer(1), 1.0);
    manager.Read(2, 5);
    manager.Read(3, 7);
    ASSERT_EQUAL(manager.Cheer(2), 0.0);
    ASSERT_EQUAL(manager.Cheer(3), 0.5);
    manager.Read(3, 10);
    ASSERT_EQUAL(manager.Cheer(3), 0.5);
    manager.Read(3, 11);
    ASSERT_EQUAL(manager.Cheer(3), 1.0);
    ASSERT_EQUAL(manager.Cheer(1), 0.5);
}

void Test2() {
    ReadingManager manager;
    manager.Read(1, 1);
    manager.Read(1, 3);
    manager.Read(2, 2);
    ASSERT_EQUAL(manager.Cheer(1), 1.0);
    ASSERT_EQUAL(manager.Cheer(2), 0.0);
}

void Test3() {
    ReadingManager manager;
    manager.Read(4, 5);
    manager.Read(3, 4);
    manager.Read(2, 3);
    manager.Read(1, 2);
    ASSERT_EQUAL(manager.Cheer(3), 2.0 / 3.0);
}

void Test4() {
    const int MAX_USER_COUNT = 100'000;
    ReadingManager manager;
    ASSERT_EQUAL(manager.Cheer(MAX_USER_COUNT), 0.0);
    manager.Read(MAX_USER_COUNT, 1000);

    ASSERT_EQUAL(manager.Cheer(MAX_USER_COUNT), 1.0);

}


void Test5() {

    ReadingManager manager;
    manager.Read(1, 1);
    ASSERT_EQUAL(manager.Cheer(100'000), 0.0);

}

void Test6() {
    ReadingManager manager;
    ASSERT_EQUAL(manager.Cheer(1), 0.0);
    manager.Read(1, 15);
    ASSERT_EQUAL(manager.Cheer(3), 0.0);
    ASSERT_EQUAL(manager.Cheer(3), 0.0);
    ASSERT_EQUAL(manager.Cheer(3), 0.0);
    manager.Read(1, 17);
    ASSERT_EQUAL(manager.Cheer(1), 1.0);
    ASSERT_EQUAL(manager.Cheer(3), 0.0);
    ASSERT_EQUAL(manager.Cheer(3), 0.0);
    ASSERT_EQUAL(manager.Cheer(3), 0.0);

}

void Test_All() {
    TestRunner tr;
    RUN_TEST(tr, Test1);
    RUN_TEST(tr, Test2);
    RUN_TEST(tr, Test3);
    RUN_TEST(tr, Test4);
    RUN_TEST(tr, Test5);
    RUN_TEST(tr, Test6);


}

#endif