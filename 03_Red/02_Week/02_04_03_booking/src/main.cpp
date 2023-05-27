#include <iomanip>
#include <iostream>
#include <fstream>
#include <map>
#include <set>

#include <deque>

#include "test_runner.h"
#include "profile.h"

#define MAX_CLIENT_ID 1'000'000'000
#define MAX_ROOM_COUNT 1'000
#define MAX_TIME 1'000'000'000'000'000'000
#define MIN_TIME -MAX_TIME

#define DAY_TIME_SIZE 86'400

using namespace std;


void Test_All();

struct Booking {
    int64_t booking_time;
    int client_id;
    int room_count;
};

class BookingManager {
private:

    map<string, deque<Booking>> store;
    int64_t current_time;
    void CleanHotel(const string& hotel_name);

public:
    BookingManager() {};
    ~BookingManager() {};

    void Book(int64_t current_time, const string& hotel_name, int client_id, int room_count);
    int Clients(const string& hotel_name);
    int Rooms(const string& hotel_name);
};

void BookingManager::CleanHotel(const string& hotel_name) {
    auto day_start_time = current_time - DAY_TIME_SIZE;
    for (auto& hotel = store[hotel_name]; hotel.front().booking_time <= day_start_time; hotel.pop_front()) {}
}

void BookingManager::Book(int64_t current_time, const string& hotel_name, int client_id, int room_count) {

    auto& hotel = store[hotel_name];
    hotel.push_back({ current_time, client_id, room_count });

    this->current_time = current_time;
}

int BookingManager::Clients(const string& hotel_name) {

    if (store.count(hotel_name) == 0) return 0;

    CleanHotel(hotel_name);

    set<int> clients;
    for (const auto& item : store.at(hotel_name)) {
        clients.insert(item.client_id);
    }
    return clients.size();
}

int BookingManager::Rooms(const string& hotel_name) {

    if (store.count(hotel_name) == 0) return 0;

    CleanHotel(hotel_name);

    int rooms = 0;
    for (const auto& item : store.at(hotel_name)) {
        rooms += item.room_count;
    }
    return rooms;
}

int main() {

    Test_All();

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // ifstream cin("input.txt");

    BookingManager manager;

    int query_count;
    cin >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id) {
        string query_type;
        cin >> query_type;

        if (query_type == "BOOK") {
            int64_t time;
            string hotel_name;
            int client_id;
            int room_count;
            cin >> time >> hotel_name >> client_id >> room_count;
            manager.Book(time, hotel_name, client_id, room_count);
        } else if (query_type == "CLIENTS") {
            string hotel_name;
            cin >> hotel_name;
            cout << manager.Clients(hotel_name) << "\n";
        } else if (query_type == "ROOMS") {
            string hotel_name;
            cin >> hotel_name;
            cout << manager.Rooms(hotel_name) << "\n";
        }
    }
    return 0;
}

void Test0() {
    BookingManager manager;
    ASSERT_EQUAL(manager.Clients("Marriot"), 0);
    ASSERT_EQUAL(manager.Rooms("Marriot"), 0);
    manager.Book(10, "FourSeasons", 1, 2);
    manager.Book(10, "Marriot", 1, 1);
    manager.Book(86409, "FourSeasons", 2, 1);
    ASSERT_EQUAL(manager.Clients("FourSeasons"), 2);
    ASSERT_EQUAL(manager.Rooms("FourSeasons"), 3);
    ASSERT_EQUAL(manager.Clients("Marriot"), 1);
    manager.Book(86410, "Marriot", 2, 10);
    ASSERT_EQUAL(manager.Rooms("FourSeasons"), 1);
    ASSERT_EQUAL(manager.Rooms("Marriot"), 10);

}

void Test1() {

    BookingManager manager;
    manager.Book(10, "a", 1, 1);
    manager.Book(10, "a", 1, 1);
    manager.Book(10, "a", 1, 1);
    manager.Book(10, "a", 1, 1);

    ASSERT_EQUAL(manager.Clients("a"), 1);
    ASSERT_EQUAL(manager.Rooms("a"), 4);

    manager.Book(86410, "a", 1, 1);

    ASSERT_EQUAL(manager.Clients("a"), 1);
    ASSERT_EQUAL(manager.Rooms("a"), 1);
}

void Test2() {
    BookingManager hm;

    ASSERT_EQUAL(hm.Rooms("a"), 0);
    ASSERT_EQUAL(hm.Clients("a"), 0);
    hm.Book(-100000, "a", 100000, 1000);
    hm.Book(-100000, "a", 100003, 1000);
    hm.Book(-100000, "b", 100002, 1000);
    ASSERT_EQUAL(hm.Rooms("a"), 2000);
    ASSERT_EQUAL(hm.Clients("a"), 2);
    hm.Book(-10000, "a", 100002, 1000);
    ASSERT_EQUAL(hm.Rooms("a"), 1000);
    ASSERT_EQUAL(hm.Clients("a"), 1);
    ASSERT_EQUAL(hm.Rooms("b"), 0);
    ASSERT_EQUAL(hm.Clients("b"), 0);
}

void Test3() {
    BookingManager b;
    ASSERT_EQUAL(b.Rooms("a"), 0);
    ASSERT_EQUAL(b.Clients("a"), 0);

    b.Book(10, "a", 1, 50);
    b.Book(20, "a", 1, 50);
    ASSERT_EQUAL(b.Rooms("a"), 100);
    ASSERT_EQUAL(b.Clients("a"), 1);
    b.Book(86410, "a", 1, 1);
    ASSERT_EQUAL(b.Rooms("a"), 51);
    ASSERT_EQUAL(b.Clients("a"), 1);
}

void Test4() {
    BookingManager b;

    ASSERT_EQUAL(b.Rooms("a"), 0);
    ASSERT_EQUAL(b.Clients("a"), 0);

    ASSERT_EQUAL(b.Rooms("b"), 0);
    ASSERT_EQUAL(b.Clients("c"), 0);

    b.Book(-100000, "a", 100000, 1000);
    b.Book(-100000, "a", 100003, 1000);
    b.Book(-100000, "b", 100002, 1000);
    ASSERT_EQUAL(b.Rooms("a"), 2000);
    ASSERT_EQUAL(b.Clients("a"), 2);

    b.Book(-10000, "a", 100002, 1000);
    ASSERT_EQUAL(b.Rooms("a"), 1000);
    ASSERT_EQUAL(b.Clients("a"), 1);
    ASSERT_EQUAL(b.Rooms("b"), 0);
    ASSERT_EQUAL(b.Clients("b"), 0);
}

void Test5() {
    BookingManager mn;
    ASSERT_EQUAL(mn.Rooms("a"), 0);
    ASSERT_EQUAL(mn.Clients("a"), 0);

    mn.Book(MIN_TIME, "a", MAX_CLIENT_ID, MAX_ROOM_COUNT);
    ASSERT_EQUAL(mn.Rooms("a"), MAX_ROOM_COUNT);
    ASSERT_EQUAL(mn.Clients("a"), 1);

    mn.Book(MIN_TIME, "a", MAX_CLIENT_ID, MAX_ROOM_COUNT);
    mn.Book(MIN_TIME, "b", MAX_CLIENT_ID, MAX_ROOM_COUNT);
    ASSERT_EQUAL(mn.Rooms("a"), 2 * MAX_ROOM_COUNT);
    ASSERT_EQUAL(mn.Rooms("b"), MAX_ROOM_COUNT);
    ASSERT_EQUAL(mn.Clients("a"), 1);
    ASSERT_EQUAL(mn.Clients("b"), 1);

    mn.Book(MIN_TIME + DAY_TIME_SIZE - 1, "a", MAX_CLIENT_ID, MAX_ROOM_COUNT);
    mn.Book(MIN_TIME + DAY_TIME_SIZE - 1, "b", MAX_CLIENT_ID, MAX_ROOM_COUNT);
    ASSERT_EQUAL(mn.Rooms("a"), 3 * MAX_ROOM_COUNT);
    ASSERT_EQUAL(mn.Rooms("b"), 2 * MAX_ROOM_COUNT);
    ASSERT_EQUAL(mn.Clients("a"), 1);
    ASSERT_EQUAL(mn.Clients("b"), 1);

    mn.Book(MIN_TIME + DAY_TIME_SIZE, "a", MAX_CLIENT_ID, 1);
    mn.Book(MIN_TIME + DAY_TIME_SIZE, "b", MAX_CLIENT_ID, 1);
    ASSERT_EQUAL(mn.Rooms("a"), 1001);
    ASSERT_EQUAL(mn.Rooms("b"), 1001);
    ASSERT_EQUAL(mn.Clients("a"), 1);
    ASSERT_EQUAL(mn.Clients("b"), 1);



    mn.Book(MAX_TIME, "a", MAX_CLIENT_ID, MAX_ROOM_COUNT);
    ASSERT_EQUAL(mn.Rooms("a"), MAX_ROOM_COUNT);
    ASSERT_EQUAL(mn.Clients("a"), 1);

}

void Test6() {
    BookingManager bm;
    bm.Book(10, "a", 1, 5);
    bm.Book(86410, "b", 1, 5);
    ASSERT_EQUAL(bm.Clients("a"), 0);
    ASSERT_EQUAL(bm.Rooms("a"), 0);
}
void Test_All() {
    TestRunner tr;
    RUN_TEST(tr, Test0);
    RUN_TEST(tr, Test1);
    RUN_TEST(tr, Test2);
    RUN_TEST(tr, Test3);
    RUN_TEST(tr, Test4);
    RUN_TEST(tr, Test5);
    RUN_TEST(tr, Test6);

}