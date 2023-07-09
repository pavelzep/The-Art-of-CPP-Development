#pragma once

#include <cstdlib>
#include <iostream>

using namespace std;

template <typename T>
class SimpleVector {
public:
    SimpleVector();
    explicit SimpleVector(size_t size);
    SimpleVector(const SimpleVector& other);
    ~SimpleVector();

    T& operator[](size_t index);
    void operator=(const SimpleVector& other);

    T* begin();
    T* end();

    const T* begin() const;
    const T* end() const;

    size_t Size() const;
    size_t Capacity() const;
    void PushBack(const T& value);

private:
    T* data = nullptr;
    T* end_ = nullptr;

    size_t size_ = 0;
    size_t capacity_ = 0;

    void reserve(size_t new_cap);
};

template<typename T>
inline SimpleVector<T>::SimpleVector() :size_(0), capacity_(0) {
}

template<typename T>
inline SimpleVector<T>::SimpleVector(size_t size) : SimpleVector() {
    data = new T[size];
    end_ = data + size;
    size_ = size;
    capacity_ = size;
}

template<typename T>
inline SimpleVector<T>::SimpleVector(const SimpleVector& other) :
    data(new T[other.capacity_]),
    size_(other.size_),
    capacity_(other.capacity_) {
    copy(other.begin().other.end(), begin());
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
    data = new T[other.capacity_];
    size_ = other.size_;
    capacity_ = other.capacity_;
    end_ = data + size_;
    for (size_t i = 0; i < capacity_; i++) {
        data[i] = other.data[i];
    }
}

template<typename T>
inline T* SimpleVector<T>::begin() {
    return data;
}

template<typename T>
inline T* SimpleVector<T>::end() {
    return end_;
}

template<typename T>
inline const T* SimpleVector<T>::begin() const {
    return data;
}

template<typename T>
inline const T* SimpleVector<T>::end() const {
    return end_;
}

template<typename T>
inline size_t SimpleVector<T>::Size() const {
    return size_;
}

template<typename T>
inline size_t SimpleVector<T>::Capacity() const {
    return capacity_;
}

template<typename T>
inline void SimpleVector<T>::PushBack(const T& value) {
    if (Size() == 0) {
        reserve(1);
    }
    if (Size() == Capacity()) {
        reserve(capacity_ * 2);
    }
    data[size_] = value;
    size_++;
    end_ = data + size_;
}

template<typename T>
inline void SimpleVector<T>::reserve(size_t new_cap) {
    if (new_cap <= capacity_) return;
    T* new_data = new T[new_cap];

    for (size_t i = 0; i < size_; ++i) {
        new_data[i] = data[i];
    }

    delete[] data;
    data = new_data;
    capacity_ = new_cap;
}

template <typename T>
ostream& operator <<(ostream& out, SimpleVector<T>& vector) {
    for (const auto& item : vector) {
        out << item << ' ';
    }
    return out;
}