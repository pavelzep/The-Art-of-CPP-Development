#include "test_runner.h"

#include <numeric>
#include <vector>
#include <string>
#include <future>
#include <mutex>
#include <queue>
#include <thread>
using namespace std;

template <typename T>
class Synchronized {
public:
    explicit Synchronized(T initial = T()) {

    }

    struct Access {
        lock_guard <mutex> g;
        T& ref_to_value;

    };

    Access GetAccess() {

        return Access{ m, value };
    }
private:
    T value;
    mutex m;
};


vector<int> Consume(Synchronized<deque<int>>& common_queue) {
    vector<int> got;

    for (;;) {
        deque<int> q;

        {
            auto access = common_queue.GetAccess();
            q = move(access.ref_to_value);
        }

        for (int item : q) {
            if (item > 0) {
                got.push_back(item);
            } else {
                return got;
            }
        }
    }
}

