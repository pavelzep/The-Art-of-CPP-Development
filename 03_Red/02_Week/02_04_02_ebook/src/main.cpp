#include <iomanip>
#include <iostream>
#include <map>
#include <set>


using namespace std;

class ReadingManager {
public:
    ReadingManager() {

    }

    void Read(int user, int page) {
        user_to_page[user] = page;


        page_to_user[page].insert(user);


    }

    double Cheer(int user
    ) const {


    }

private:

    map <int, set<int>> page_to_user;
    map <int, int> user_to_page;
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