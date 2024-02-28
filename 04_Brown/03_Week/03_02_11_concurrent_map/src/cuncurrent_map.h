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

  explicit ConcurrentMap(size_t bucket_count);

  WriteAccess operator[](const K& key);
  ReadAccess At(const K& key) const;

  bool Has(const K& key) const;

  MapType BuildOrdinaryMap() const;

private:
  Hash hasher;
};

template<typename K, typename V, typename Hash>
inline ConcurrentMap<K, V, Hash>::ConcurrentMap(size_t bucket_count) {
}

template<typename K, typename V, typename Hash>
inline typename ConcurrentMap<K, V, Hash>::WriteAccess ConcurrentMap<K, V, Hash>::operator[](const K& key) {
    return WriteAccess();
}

template<typename K, typename V, typename Hash>
inline typename ConcurrentMap<K, V, Hash>::ReadAccess ConcurrentMap<K, V, Hash>::At(const K& key) const {
    return ReadAccess();
}

template<typename K, typename V, typename Hash>
inline bool ConcurrentMap<K, V, Hash>::Has(const K& key) const {
    return false;
}

template<typename K, typename V, typename Hash>
inline typename ConcurrentMap<K, V, Hash>::MapType ConcurrentMap<K, V, Hash>::BuildOrdinaryMap() const {
    return MapType();
}
