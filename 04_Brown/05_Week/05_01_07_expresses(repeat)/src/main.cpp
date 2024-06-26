#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <set>

using namespace std;

class RouteManager {
public:
    void AddRoute(int start, int finish) {
        reachable_lists_[start].insert(finish);
        reachable_lists_[finish].insert(start);
    }
    int FindNearestFinish(int start, int finish) const {
        int result = abs(start - finish);
        if (reachable_lists_.count(start) < 1) {
            return result;
        }
        const set<int>& reachable_stations = reachable_lists_.at(start);
        if (!reachable_stations.empty()) {

            auto it = FindNearestElement(reachable_stations, finish);
            result = min(result, abs(*it - finish));
        }
        return result;
    }
private:

    map<int, set<int>> reachable_lists_;

    set<int>::const_iterator FindNearestElement(const set<int>& numbers, int border) const {
        auto right = numbers.lower_bound(border);
        if (right == numbers.begin()) return numbers.begin();
        auto left = prev(right);
        if (right == numbers.end()) return left;
        if (border - *right <= *left - border)
            return left;
        else
            return right;
    }
};


int main() {
    RouteManager routes;
    int query_count;
    cin >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id) {
        string query_type;
        cin >> query_type;
        int start, finish;
        cin >> start >> finish;
        if (query_type == "ADD") {
            routes.AddRoute(start, finish);
        } else if (query_type == "GO") {
            cout << routes.FindNearestFinish(start, finish) << "\n";
        }
    }
    return 0;
}


