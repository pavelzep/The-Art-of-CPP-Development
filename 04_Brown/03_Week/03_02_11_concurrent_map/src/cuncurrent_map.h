#pragma once


#include <future>
#include <mutex>
#include <unordered_map>
#include <vector>
#include <utility>
#include <algorithm>
#include <random>
#include <numeric>

using namespace std;

template <typename K, typename V, typename Hash = std::hash<K>>
class ConcurrentMap {
public:
    using MapType = unordered_map<K, V, Hash>;

    struct WriteAccess {
        lock_guard <mutex> g;
        V& ref_to_value;
    };

    struct ReadAccess {
        lock_guard <mutex> g;
        const V& ref_to_value;
    };

    explicit ConcurrentMap(size_t _bucket_count) : bucket_count(_bucket_count) {
        for (size_t i = 0; i < bucket_count; ++i) {
            storage.push_back(MapType());
            mutexes.push_back(make_unique<std::mutex>());
        }
    }

    WriteAccess operator[](const K& key) {

        size_t bucket_number = hasher(key) % bucket_count;
        return { lock_guard(*mutexes[bucket_number]),storage[bucket_number][key] };
    }
    ReadAccess At(const K& key) const {
        size_t bucket_number = hasher(key) % bucket_count;
        return { lock_guard(*mutexes[bucket_number]),storage[bucket_number].at(key) };
    }



    bool Has(const K& key) const {

        size_t bucket_number = hasher(key) % bucket_count;
        // lock_guard(*mutexes[bucket_number]);
        mutex help_mutex;
        if (lock_guard g(help_mutex); storage[hasher(key) % bucket_count].count(key)) {
            return true;
        } else return false;
    }

    MapType BuildOrdinaryMap() const {
        MapType result;

        for (size_t i = 0; i < bucket_count; ++i) {
            lock_guard g(*mutexes[i]);
            auto m = storage[i];
            result.merge(m);
        }

        return result;
    }

private:
    Hash hasher;
    vector <MapType> storage;
    vector <unique_ptr<mutex>>mutexes;
    size_t bucket_count;
};