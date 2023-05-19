#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <fstream>


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
        if (user_count==1) return 1.0;
        if (it == user_to_page.end()) return {};
        return 1-(pages[it->second-1]-1) * 1.0 / (user_count-1);
    }

private:
    int user_count;
    map <int, int> user_to_page;
    vector <int> pages;
};


int main() {
    // fstream cin("../input.txt");

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