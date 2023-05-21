#pragma once
#include <string>

#define MAX_CLIENT_ID 1'000'000'000
#define MAX_ROOM_COUNT 1'000
#define MIN_TIME -1'000'000'000'000'000'000
#define MAX_TIME 1'000'000'000'000'000'000
#define MAX_SIZE_TIME 86'400

using namespace std;

struct booking {

};

class BookingManager {
private:



public:
    BookingManager() {};
    ~BookingManager() {};

    void Book(int64_t time, const string& hotel_name, int client_id, int room_count);
    int Clients(const string& hotel_name) const;
    int Rooms(const string& hotel_name) const;
};

void BookingManager::Book(int64_t time, const string& hotel_name, int client_id, int room_count) {
}

int BookingManager::Clients(const string& hotel_name) const {
    return 0;
}

int BookingManager::Rooms(const string& hotel_name) const {
    return 0;
}
