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

    explicit ConcurrentMap(size_t bucket_count) {
        vector<map< K, V>> storage(bucket_count);
    }

    Access operator[](const K& key) {
        storage[current_bucket_index].count(key)

    }

    map<K, V> BuildOrdinaryMap() {

    }
    private:
    size_t current_bucket_index;
    void indexUpdate(){
        current_bucket_index++;
        if (current_bucket_index == bucket_count) current_bucket_index = 0;
    }
};