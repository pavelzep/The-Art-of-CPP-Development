#pragma once

#include <cstdlib>

// Реализуйте шаблон SimpleVector
template <typename T>
class SimpleVector {
public:
    SimpleVector();
    explicit SimpleVector(size_t size);
    ~SimpleVector();

    T& operator[](size_t index);

    T* begin();
    T* end();

    size_t Size() const;
    size_t Capacity() const;
    void PushBack(const T& value);

private:
    T* data = nullptr;
    
};

template<typename T>
inline SimpleVector<T>::SimpleVector() {
}

template<typename T>
inline SimpleVector<T>::SimpleVector(size_t size) {
}

template<typename T>
inline SimpleVector<T>::~SimpleVector() {
}

template<typename T>
inline T& SimpleVector<T>::operator[](size_t index) {
    // TODO: вставьте здесь оператор return
}

template<typename T>
inline T* SimpleVector<T>::begin() {
    return nullptr;
}

template<typename T>
inline T* SimpleVector<T>::end() {
    return nullptr;
}

template<typename T>
inline size_t SimpleVector<T>::Size() const {
    return size_t();
}

template<typename T>
inline size_t SimpleVector<T>::Capacity() const {
    return size_t();
}

template<typename T>
inline void SimpleVector<T>::PushBack(const T& value) {
}
