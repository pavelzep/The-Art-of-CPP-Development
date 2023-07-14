#pragma once

#include <cstdint>
#include <iostream>

using namespace std;

template <typename T>
class SimpleVector {
public:
    SimpleVector() = default;
    explicit SimpleVector(size_t _size);
    SimpleVector(const SimpleVector& other);
    SimpleVector(SimpleVector&& other);
    ~SimpleVector();

    T& operator[](size_t index);
    void operator=(const SimpleVector& other);
    void operator=(SimpleVector&& other);

    T* begin() { return data; }
    T* end() { return data + size; }

    const T* begin() const { return data; }
    const T* end()  const { return data + size; }

    size_t Size() const { return size; }
    size_t Capacity() const { return capacity; }
    void PushBack(const T& value);
    void PushBack(T&& value);

private:

    T* data = nullptr;
    size_t size = 0;
    size_t capacity = 0;
    void reserve(size_t new_cap);
};

template<typename T>
inline SimpleVector<T>::SimpleVector(size_t _size)
    : data(new T[_size])
    , size(_size)
    , capacity(_size) {
}

template<typename T>
inline SimpleVector<T>::SimpleVector(const SimpleVector& other) :
    data(new T[other.capacity]),
    size(other.size),
    capacity(other.capacity) {
    copy(other.begin(), other.end(), begin());
}

template<typename T>
inline SimpleVector<T>::SimpleVector(SimpleVector&& other) :
    size(other.size),
    capacity(other.capacity) {
    delete[] data;
    move(other.begin(), other.end(), begin());
}

template<typename T>
inline void SimpleVector<T>::operator=(SimpleVector&& other) {
    delete[] data;
    data = other.data;
    size = other.size;
    capacity = other.capacity;
}

template<typename T>
inline SimpleVector<T>::~SimpleVector() {
    delete[] data;
}

template<typename T>
inline T& SimpleVector<T>::operator[](size_t index) {
    return *(data + index);
}

template<typename T>
inline void SimpleVector<T>::operator=(const SimpleVector& other) {
    delete[] data;
    data = new T[other.capacity];
    size = other.size;
    capacity = other.capacity;
    copy(other.begin(), other.end(), begin());
}

template<typename T>
inline void SimpleVector<T>::PushBack(const T& value) {
    if (Size() == 0) {
        reserve(1);
    }
    if (Size() == Capacity()) {
        reserve(capacity * 2);
    }
    data[size] = value;
    size++;
}

template<typename T>
inline void SimpleVector<T>::PushBack(T&& value) {
    if (Size() == 0) {
        reserve(1);
    }
    if (Size() == Capacity()) {
        reserve(capacity * 2);
    }

    data[size] = move(value);
    size++;
}

template<typename T>
inline void SimpleVector<T>::reserve(size_t new_cap) {
    if (new_cap <= capacity) return;
    T* new_data = new T[new_cap];

    for (size_t i = 0; i < size; ++i) {
        new_data[i] = move(data[i]);
    }

    delete[] data;
    data = new_data;
    capacity = new_cap;
}

template <typename T>
ostream& operator <<(ostream& out, SimpleVector<T>& vector) {
    for (const auto& item : vector) {
        out << item << ' ';
    }
    return out;
}