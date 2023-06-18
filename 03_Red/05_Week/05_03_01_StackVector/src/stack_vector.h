#pragma once
#include <array>
#include <stdexcept>
using namespace std;

template <typename T, size_t N>
class StackVector {
public:
    explicit StackVector(size_t a_size = 0) {
        
    }

    T& operator[](size_t index) { return store[index]; }
    const T& operator[](size_t index) const { return store[index]; }

    auto begin() { return &store[0]; }
    auto end() { return &store[0]; }
    auto begin() const { return &store[0]; }
    auto end() const { return &store[0]; }

    size_t Size() const {
        return size_t();
    }
    size_t Capacity() const { return N; }

    void PushBack(const T& value) {

    };
    T PopBack() {
        return T();
    }

private:
    array<T, N> store;

};