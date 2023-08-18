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
        bucket_count(_bucket_count) {
        for (size_t i = 0; i < bucket_count; ++i) {
            storage.push_back(map<K, V>());
            mutexes.push_back(make_unique<std::mutex>());
        }
    }

    Access operator[](const K& key) {
        return { lock_guard(*mutexes[key % bucket_count]),storage[key % bucket_count][key] };
    }

    map<K, V> BuildOrdinaryMap() {
        map<K, V> result;

        for (size_t i = 0; i < bucket_count; ++i) {
            lock_guard g(*mutexes[i]);
            result.merge(storage[i]);
        }
        return result;
    }

private:
    vector <map <K, V>> storage;
    vector <unique_ptr<mutex>>mutexes;
    size_t bucket_count;
};