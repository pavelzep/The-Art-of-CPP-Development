#include "test_runner.h"
#include "profile.h"

#include <cstdint>
#include <iterator>
#include <numeric>
#include <vector>
#include <utility>
#include <list>

using namespace std;


template <typename RandomIt>
void MakeJosephusPermutation(RandomIt first, RandomIt last, uint32_t step_size) {
    list <typename RandomIt::value_type> pool;
    {
        auto it = first;
        while (it != last) {
            pool.push_back(move(*it));
            ++it;
        }
    }

    size_t cur_pos = 0;
    auto it = pool.begin();
    {
        auto my_advance = [](list <typename RandomIt::value_type>& lst, auto& it, uint32_t step_size) -> auto {
            auto last_it = prev(end(lst));
            while (step_size) {
                if (it != last_it) it = next(it);
                else it = begin(lst);
                --step_size;
            }
            };
        auto for_del = it;
        while (!pool.empty()) {
            for_del = it;
            *(first++) = move(*it);
            my_advance(pool, it, 1);
            pool.erase(for_del);
            if (pool.empty()) return;
            my_advance(pool, it, step_size - 1);
        }
    }





    // while (!pool.empty()) {
    //     auto it = pool.begin();
    //     advance(it, cur_pos);
    //     *(first++) = move(*it);
    //     pool.erase(it);
    //     if (pool.empty()) {
    //         break;
    //     }
    //     cur_pos = (cur_pos + step_size - 1) % pool.size();
    // }
}

// template <typename RandomIt>
// void MakeJosephusPermutation(RandomIt first, RandomIt last, uint32_t step_size) {
//     vector<typename RandomIt::value_type> pool;
//     auto it = first;
//     while (it != last) {
//         pool.push_back(move(*it));
//         ++it;
//     }
//     size_t cur_pos = 0;
//     while (!pool.empty()) {
//         *(first++) = move(pool[cur_pos]);
//         pool.erase(pool.begin() + cur_pos);
//         if (pool.empty()) {
//             break;
//         }
//         cur_pos = (cur_pos + step_size - 1) % pool.size();
//     }
// }

vector<int> MakeTestVector() {
    vector<int> numbers(10);
    iota(begin(numbers), end(numbers), 0);
    return numbers;
}

vector<int> MakeIntVector_(size_t size) {
    vector<int> numbers(size);
    iota(begin(numbers), end(numbers), 0);
    return numbers;
}

void TestIntVector() {
    const vector<int> numbers = MakeTestVector();
    {
        vector<int> numbers_copy = numbers;
        MakeJosephusPermutation(begin(numbers_copy), end(numbers_copy), 1);
        ASSERT_EQUAL(numbers_copy, numbers);
    }
    {
        vector<int> numbers_copy = numbers;
        MakeJosephusPermutation(begin(numbers_copy), end(numbers_copy), 3);
        ASSERT_EQUAL(numbers_copy, vector<int>({ 0, 3, 6, 9, 4, 8, 5, 2, 7, 1 }));
    }
}

// Это специальный тип, который поможет вам убедиться, что ваша реализация
// функции MakeJosephusPermutation не выполняет копирование объектов.
// Сейчас вы, возможно, не понимаете как он устроен, однако мы расскажем,
// почему он устроен именно так, далее в блоке про move-семантику —
// в видео «Некопируемые типы»

struct NoncopyableInt {
    int value;

    NoncopyableInt(const NoncopyableInt&) = delete;
    NoncopyableInt& operator=(const NoncopyableInt&) = delete;

    NoncopyableInt(NoncopyableInt&&) = default;
    NoncopyableInt& operator=(NoncopyableInt&&) = default;
};

bool operator == (const NoncopyableInt& lhs, const NoncopyableInt& rhs) {
    return lhs.value == rhs.value;
}

ostream& operator << (ostream& os, const NoncopyableInt& v) {
    return os << v.value;
}

void TestAvoidsCopying() {
    vector<NoncopyableInt> numbers;
    numbers.push_back({ 1 });
    numbers.push_back({ 2 });
    numbers.push_back({ 3 });
    numbers.push_back({ 4 });
    numbers.push_back({ 5 });

    MakeJosephusPermutation(begin(numbers), end(numbers), 2);

    vector<NoncopyableInt> expected;
    expected.push_back({ 1 });
    expected.push_back({ 3 });
    expected.push_back({ 5 });
    expected.push_back({ 4 });
    expected.push_back({ 2 });

    ASSERT_EQUAL(numbers, expected);
}


void Test_10000_1() {
    auto vect = MakeIntVector_(100000);
    MakeJosephusPermutation(begin(vect), end(vect), 1);
}

void Test_10000_100() {
    auto vect = MakeIntVector_(100000);
    MakeJosephusPermutation(begin(vect), end(vect), 100);
}
void Test_3_3() {
    auto vect = MakeIntVector_(3);
    MakeJosephusPermutation(begin(vect), end(vect), 3);
}

void Test_10_1() {
    auto vect = MakeIntVector_(10);
    MakeJosephusPermutation(begin(vect), end(vect), 1);
}

void Test_1_100000() {
    auto vect = MakeIntVector_(1);
    MakeJosephusPermutation(begin(vect), end(vect), 100000);
}

int main() {
    TestRunner tr;

    RUN_TEST(tr, TestIntVector);
    RUN_TEST(tr, TestAvoidsCopying);

    RUN_TEST(tr, Test_10_1);
    RUN_TEST(tr, Test_3_3);
    RUN_TEST(tr, Test_1_100000);
    {
        LOG_DURATION("Test_10000_1");
        RUN_TEST(tr, Test_10000_1);
    }
    {
        LOG_DURATION("Test_10000_100");
        RUN_TEST(tr, Test_10000_100);
    }
    return 0;
}
