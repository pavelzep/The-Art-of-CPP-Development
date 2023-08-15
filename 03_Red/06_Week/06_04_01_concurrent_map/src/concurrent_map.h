#pragma once


#include <algorithm>
#include <numeric>
#include <random>
#include <future>
#include <map>

using namespace std;

template <typename K, typename V>
class ConcurrentMap {
public:
    static_assert(is_integral_v<K>, "ConcurrentMap supports only integer keys");

    struct Access {
        V& ref_to_value;
    };

    explicit ConcurrentMap(size_t _bucket_count) :
        bucket_count(_bucket_count) {

    }

    Access operator[](const K& key) {
        for (size_t i = 0; i < current_bucket_index; ++i) {

            if (storage[i].count(key)) {
                return { storage[i][key] };
            }

            return { storage[current_bucket_index][key] };


        }
    }
    map<K, V> BuildOrdinaryMap() {

    }
private:
    vector<map< K, V>> storage;
    size_t bucket_count;
    size_t current_bucket_index;

    void indexUpdate() {
        current_bucket_index++;
        if (current_bucket_index == bucket_count) current_bucket_index = 0;
    }
};