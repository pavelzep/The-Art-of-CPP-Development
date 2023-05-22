#pragma once

#include <string>
#include <vector>

#define MAX_CLIENT_ID 1'000'000'000
#define MAX_ROOM_COUNT 1'000
#define MIN_TIME -1'000'000'000'000'000'000
#define MAX_TIME 1'000'000'000'000'000'000
#define MAX_SIZE_TIME 86'400

using namespace std;

struct booking {
    int client_id;
    int room_count;
};

class hotel {
private:

    int clients_count;
    int room_count;
    vector<booking> bookings;
    int64_t start_time;

public:
    hotel() :
        bookings(MAX_SIZE_TIME, { 0,0 }) {
    };

    void add(int64_t time, int client_id, int room_count) {

        int64_t current_time = time - start_time;
        if(current_time>MAX_SIZE_TIME)
        
 
    }
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
