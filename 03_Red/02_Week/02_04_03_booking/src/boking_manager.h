#pragma once

#include <string>
#include <vector>
#include <deque>
#include <algorithm>

#define MAX_CLIENT_ID 1'000'000'000
#define MAX_ROOM_COUNT 1'000
#define MIN_TIME -1'000'000'000'000'000'000
#define MAX_TIME 1'000'000'000'000'000'000
#define DAY_TIME_SIZE 86'400

using namespace std;

struct Booking {
    int64_t booking_time;
    string hotel_name;
    int client_id;
    int room_count;
};


class BookingManager {
private:

    deque<Booking> store;

public:
    BookingManager() {};
    ~BookingManager() {};

    void Book(int64_t current_time, const string& hotel_name, int client_id, int room_count);
    int Clients(const string& hotel_name) const;
    int Rooms(const string& hotel_name) const;
};

void BookingManager::Book(int64_t current_time, const string& hotel_name, int client_id, int room_count) {

    int64_t day_start_time = current_time - DAY_TIME_SIZE;

    store.push_back({ current_time, hotel_name, client_id, room_count });
    for (;store.front().booking_time <= day_start_time;store.pop_front()) {

    }



}

int BookingManager::Clients(const string& hotel_name) const {
    int result = 0;
    for (const auto& item : store) {
        item.client_id
    }
    return 0;
}

int BookingManager::Rooms(const string& hotel_name) const {
    return 0;
}
