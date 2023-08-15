#pragma once


#include <algorithm>
#include <numeric>
#include <random>

#include <map>
#include <mutex>

using namespace std;

template <typename K, typename V>
class ConcurrentMap {
public:
    static_assert(is_integral_v<K>, "ConcurrentMap supports only integer keys");

    struct Access {
        // lock_guard <mutex> guard;
        V& ref_to_value;
    };

    // struct Bucket {
    //     map <K, V> bucket_map;
    //     mutex m;
    // };

    explicit ConcurrentMap(size_t _bucket_count) :
        bucket_count(_bucket_count),
        current_bucket_index(0) {
        storage.reserve(bucket_count);
        for (size_t i = 0; i < bucket_count; ++i) {
            storage.push_back(map<K, V>());

        }

    }

    Access operator[](const K& key) {
        for (size_t i = 0; i < bucket_count; ++i) {

            if (storage[i].count(key)) {
                return { storage[i][key] };
            }
            current_bucket_index_update();
            return { storage[++current_bucket_index][key] };

        }
    }

    map<K, V> BuildOrdinaryMap() {
    }

private:
    vector< map <K, V>> storage;
    // vector<mutex> mutex_vec;
    size_t bucket_count;
    size_t current_bucket_index;

    void current_bucket_index_update() {
        if (current_bucket_index == bucket_count) current_bucket_index = 0;
    }
};