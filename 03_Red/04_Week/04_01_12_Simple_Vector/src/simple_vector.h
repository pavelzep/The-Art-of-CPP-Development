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

    size_t size = 0;
    size_t capacity = 0;


};

template<typename T>
inline SimpleVector<T>::SimpleVector():size(0), capacity(0) {
}

template<typename T>
inline SimpleVector<T>::SimpleVector(size_t size): SimpleVector() {
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
    return size;
}

template<typename T>
inline size_t SimpleVector<T>::Capacity() const {
    return capacity;
}

template<typename T>
inline void SimpleVector<T>::PushBack(const T& value) {
     if(size==0)
      
}
