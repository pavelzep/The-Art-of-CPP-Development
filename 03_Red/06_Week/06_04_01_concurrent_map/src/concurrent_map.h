#pragma once


#include <algorithm>
#include <numeric>
#include <random>
#include <memory>

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

        for (size_t i = 0; i < bucket_count; ++i) {
            storage.push_back(map<K, V>());
            mutexes.push_back(make_unique<std::mutex>());

        }
    }

    Access operator[](const K& key) {
        for (size_t i = 0; i < bucket_count; ++i) {
            if (storage[i].count(key)) {
                return { lock_guard(*mutexes[i]), storage[i][key] };
            }
        }

        {
            lock_guard g(self_mutex);
            size_t ind = current_bucket_index_update();
            return { lock_guard(*mutexes[ind]),storage[ind][key] };
        }
    }

    map<K, V> BuildOrdinaryMap() {
        lock_guard g(self_mutex);
        map<K, V> result;
        for (auto& item : storage) {
            lock_guard b_m(bucket_mutex);
            result.merge(item);
        }

        // for (size_t i = 0; i < bucket_count; ++i) {}
        return result;
    }

private:
    vector< map <K, V>> storage;
    vector <unique_ptr<mutex>>mutexes;
    size_t current_bucket_index;
    size_t bucket_count;
    mutex self_mutex, bucket_mutex;

    size_t current_bucket_index_update() {
        current_bucket_index++;
        if (current_bucket_index == bucket_count) current_bucket_index = 0;
        return current_bucket_index;
    }
};