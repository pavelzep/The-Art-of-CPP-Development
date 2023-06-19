#pragma once
#include <array>
#include <stdexcept>
#include <iterator>
using namespace std;

template <typename T, size_t N>
class StackVector {
public:
    explicit StackVector(size_t a_size = 0) {
        if (a_size > N) {
            throw invalid_argument("");
        } else {
            size = a_size;
        }
    }

    T& operator[](size_t index) { return store[index]; }
    const T& operator[](size_t index) const { return store[index]; }

    auto begin() { return &store[0]; }
    auto end() { return &store[0] + size; }
    auto begin() const { return &store[0]; }
    auto end() const { return &store[0] + size; }

    size_t Size() const {
        return size;
    }
    size_t Capacity() const { return N; }

    void PushBack(const T& value) {
        if (size < N) {
            store[size] = value;
            ++size;
        } else {
            throw overflow_error("");
        }
    };
    T PopBack() {
        if (size) {
            --size;
            return store[size];

        } else {
            throw underflow_error("");
        }
    }

private:
    array<T, N> store;
    size_t size = 0;
};