#include "test_runner.h"

#include <forward_list>
#include <iterator>
#include <vector>
#include <algorithm>

using namespace std;

template <typename Type, typename Hasher>
class HashSet {
public:
    using BucketList = forward_list<Type>;

public:
    explicit HashSet(
        size_t num_buckets,
        const Hasher& hasher = {}
    );

    void Add(const Type& value);
    bool Has(const Type& value) const;
    void Erase(const Type& value);
    const BucketList& GetBucket(const Type& value) const;

private:
    BucketList& _GetBucket(const Type& value);
    vector<BucketList> baskets;
    size_t _num_buckets;
    Hasher _hasher;
    BucketList emptyList = {};
    
    size_t Hash(const Type& value) const {
        return _hasher(value) % _num_buckets;
    };
};

template<typename Type, typename Hasher>
HashSet<Type, Hasher>::HashSet(size_t num_buckets, const Hasher& hasher) :
    _hasher(hasher),
    _num_buckets(num_buckets) {
    baskets.resize(num_buckets);
}

template<typename Type, typename Hasher>
void HashSet<Type, Hasher>::Add(const Type& value) {
    if (!Has(value)) {
        _GetBucket(value).push_front(value);
    }
}

template<typename Type, typename Hasher>
bool HashSet<Type, Hasher>::Has(const Type& value) const {
    if (baskets.size() == 0) return 0;

    const typename HashSet<Type, Hasher>::BucketList& temp_Bucket = GetBucket(value);
    auto it = find(temp_Bucket.begin(), temp_Bucket.end(), value);
    if (it != temp_Bucket.end()) return 1;

    else return 0;
}

template<typename Type, typename Hasher>
void HashSet<Type, Hasher>::Erase(const Type& value) {
    _GetBucket(value).remove(value);
}

template<typename Type, typename Hasher>
const typename HashSet<Type, Hasher>::BucketList& HashSet<Type, Hasher>::GetBucket(const Type& value) const {
    return baskets[Hash(value)];
}

template<typename Type, typename Hasher>
typename  HashSet<Type, Hasher>::BucketList& HashSet<Type, Hasher>::_GetBucket(const Type& value) {
    return baskets[Hash(value)];
}

struct IntHasher {
    size_t operator()(int value) const {
        // Это реальная хеш-функция из libc++, libstdc++.
        // Чтобы она работала хорошо, std::unordered_map
        // использует простые числа для числа бакетов
        return value;
    }
};

struct TestValue {
    int value;

    bool operator==(TestValue other) const {
        return value / 2 == other.value / 2;
    }
};

struct TestValueHasher {
    size_t operator()(TestValue value) const {
        return value.value / 2;
    }
};

void TestSmoke() {
    HashSet<int, IntHasher> hash_set(2);
    hash_set.Add(3);
    hash_set.Add(4);

    ASSERT(hash_set.Has(3));
    ASSERT(hash_set.Has(4));
    ASSERT(!hash_set.Has(5));

    hash_set.Erase(3);

    ASSERT(!hash_set.Has(3));
    ASSERT(hash_set.Has(4));
    ASSERT(!hash_set.Has(5));

    hash_set.Add(3);
    hash_set.Add(5);

    ASSERT(hash_set.Has(3));
    ASSERT(hash_set.Has(4));
    ASSERT(hash_set.Has(5));
}

void TestEmpty() {
    HashSet<int, IntHasher> hash_set(10);
    for (int value = 0; value < 10000; ++value) {
        ASSERT(!hash_set.Has(value));
    }
}

void TestIdempotency() {
    HashSet<int, IntHasher> hash_set(10);
    hash_set.Add(5);
    ASSERT(hash_set.Has(5));
    hash_set.Add(5);
    ASSERT(hash_set.Has(5));
    hash_set.Erase(5);
    ASSERT(!hash_set.Has(5));
    hash_set.Erase(5);
    ASSERT(!hash_set.Has(5));
}

void TestEquivalence() {
    HashSet<TestValue, TestValueHasher> hash_set(10);
    hash_set.Add(TestValue{ 2 });
    hash_set.Add(TestValue{ 3 });

    ASSERT(hash_set.Has(TestValue{ 2 }));
    ASSERT(hash_set.Has(TestValue{ 3 }));

    const auto& bucket = hash_set.GetBucket(TestValue{ 2 });
    const auto& three_bucket = hash_set.GetBucket(TestValue{ 3 });
    ASSERT_EQUAL(&bucket, &three_bucket);

    ASSERT_EQUAL(1, distance(begin(bucket), end(bucket)));
    ASSERT_EQUAL(2, bucket.front().value);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestSmoke);
    RUN_TEST(tr, TestEmpty);
    RUN_TEST(tr, TestIdempotency);
    RUN_TEST(tr, TestEquivalence);
    return 0;
}

