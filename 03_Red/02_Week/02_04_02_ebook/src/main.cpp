#include <iomanip>
#include <iostream>
#include <map>
#include <set>


using namespace std;

class ReadingManager {
public:
    ReadingManager() {
    }

    void Read(int user_id, int page_count) {
        
        store[user_id].insert(page_count);


    }

    double Cheer(int user_id) const {


    }

private:

    map <int, set<int>> store;

};


int main() {

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

    return 0;
}