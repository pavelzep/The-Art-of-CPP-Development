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

    }

    Access operator[](const K& key) {

    }

    map<K, V> BuildOrdinaryMap() {

    }
};