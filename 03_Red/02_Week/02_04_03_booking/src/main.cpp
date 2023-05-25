#include <iomanip>
#include <iostream>
#include <fstream>
#include <map>
#include <set>

#include <deque>

#include "test_runner.h"
#include "profile.h"

using namespace std;


void Test_All();


struct Booking {
    int64_t booking_time;
    string hotel_name;
    int client_id;
    int room_count;
};

class BookingManager {
private:

    deque<Booking> store;
    // map<string, deque<Booking>> store_;

public:
    BookingManager() {};
    ~BookingManager() {};

    void Book(int64_t current_time, const string& hotel_name, int client_id, int room_count);
    int Clients(const string& hotel_name) const;
    int Rooms(const string& hotel_name) const;
};

void BookingManager::Book(int64_t current_time, const string& hotel_name, int client_id, int room_count) {

    int64_t day_start_time = current_time - 86'400;

    store.push_back({ current_time, hotel_name, client_id, room_count });
    for (;store.front().booking_time <= day_start_time;store.pop_front()) {
    }
}

int BookingManager::Clients(const string& hotel_name) const {

    set<int> clients;
    for (const auto& item : store) {
        if (item.hotel_name == hotel_name) clients.insert(item.client_id);
    }
    return clients.size();
}

int BookingManager::Rooms(const string& hotel_name) const {
    int rooms = 0;
    for (const auto& item : store) {
        if (item.hotel_name == hotel_name)  rooms += item.room_count;
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
            int time;
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
    manager.Book(10, "FourSeasons", 1, 1);
    manager.Book(10, "FourSeasons", 1, 1);
    manager.Book(10, "FourSeasons", 1, 1);
    manager.Book(10, "FourSeasons", 1, 1);

    ASSERT_EQUAL(manager.Clients("FourSeasons"), 1);
    ASSERT_EQUAL(manager.Rooms("FourSeasons"), 4);

    manager.Book(86410, "FourSeasons", 1, 1);

    ASSERT_EQUAL(manager.Clients("FourSeasons"), 1);
    ASSERT_EQUAL(manager.Rooms("FourSeasons"), 1);
}

void Test1() {
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

void Test_All() {
    TestRunner tr;
    RUN_TEST(tr, Test0);
    RUN_TEST(tr, Test1);

}