#pragma once


#include <future>
#include <mutex>
#include <unordered_map>
#include <vector>
#include <utility>
#include <algorithm>
#include <random>

template <typename K, typename V, typename Hash = std::hash<K>>
class ConcurrentMap {
public:
    using MapType = unordered_map<K, V, Hash>;

    struct WriteAccess {
        V& ref_to_value;
    };

    struct ReadAccess {
        const V& ref_to_value;
    };

    explicit ConcurrentMap(size_t _bucket_count) : bucket_count(_bucket_count) {
        for (size_t i = 0; i < bucket_count; ++i) {
            storage.push_back(typename ConcurrentMap::MapType<K, V, Hash>());
            mutexes.push_back(make_unique<std::mutex>());
        }
    }

    WriteAccess operator[](const K& key) {
        return WriteAccess();
    }
    ReadAccess At(const K& key) const {
        return ReadAccess();
    }

    bool Has(const K& key) const {
        return false;
    }

    MapType BuildOrdinaryMap() const {
        return MapType();
    }

private:
    Hash hasher;
    vector <MapType> storage;
    vector <unique_ptr<mutex>>mutexes;
    size_t bucket_count;
};