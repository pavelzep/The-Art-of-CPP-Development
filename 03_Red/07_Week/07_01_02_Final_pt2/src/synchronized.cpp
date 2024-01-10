#include "synchronized.h"

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