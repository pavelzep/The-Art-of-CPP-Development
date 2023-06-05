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

    const T* begin() const;
    const T* end() const;

    size_t Size() const;
    size_t Capacity() const;
    void PushBack(const T& value);

private:
    T* data = nullptr;
    T* end_ = nullptr;


};

template<typename T>
inline SimpleVector<T>::SimpleVector() {


}

template<typename T>
inline SimpleVector<T>::SimpleVector(size_t size) {
    data = new T[size];
    end_ = data + size;
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
    return size_t();
}

template<typename T>
inline size_t SimpleVector<T>::Capacity() const {
    return size_t();
}

template<typename T>
inline void SimpleVector<T>::PushBack(const T& value) {
}
