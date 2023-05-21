#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <vector>

#include "profile.h"
#include "boking_manager.h"
#include "tests.h"

using namespace std;

int main() {

    Test_All();

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    BookingManager manager;


    int query_count;
    cin >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id) {
        string query_type;
        cin >> query_type;
        int user_id;
        cin >> user_id;

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

