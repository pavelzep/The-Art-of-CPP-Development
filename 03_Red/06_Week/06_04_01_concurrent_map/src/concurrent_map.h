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
        lock_guard <mutex> guard;
        V& ref_to_value;
    };

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
            mutex m;

            if (storage[i].count(key)) {
                return { lock_guard(m), storage[i][key] };
            }
        }
        {
            mutex m;
            return { lock_guard(m),storage[current_bucket_index_update()][key] };
        }
    }

    map<K, V> BuildOrdinaryMap() {
        map<K, V> result;
        for (auto& item : storage) {
            result.merge(item);
        }
        return result;
    }

private:
    vector< map <K, V>> storage;
    size_t bucket_count;
    size_t current_bucket_index;

    size_t current_bucket_index_update() {
        current_bucket_index++;
        if (current_bucket_index == bucket_count) current_bucket_index = 0;

        return current_bucket_index;
    }
};