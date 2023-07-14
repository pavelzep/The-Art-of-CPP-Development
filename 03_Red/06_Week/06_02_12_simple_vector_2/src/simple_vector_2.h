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

    T* begin();
    T* end();

    const T* begin() const;
    const T* end() const;

    size_t Size() const;
    size_t Capacity() const;
    void PushBack(const T& value);
    void PushBack(T&& value);

private:

    T* data = nullptr;
    size_t size = 0;
    size_t capacity = 0;
    void reserve(size_t new_cap);
};


// template<typename T>
// inline SimpleVector<T>::SimpleVector() :size(0), capacity(0) {
// }

template<typename T>
inline SimpleVector<T>::SimpleVector(size_t _size) : SimpleVector() {
    data = new T[_size];
    size = _size;
    capacity = _size;
}

template<typename T>
inline SimpleVector<T>::SimpleVector(const SimpleVector& other) :
    data(new T[other.capacity]),
    size(other.size),
    capacity(other.capacity) {
    copy(other.begin(), other.end(), begin());
}

template<typename T>
inline SimpleVector<T>::SimpleVector(SimpleVector&& other) {
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
    // for (size_t i = 0; i < capacity; i++) {
    //     data[i] = other.data[i];
    // }
}

template<typename T>
inline T* SimpleVector<T>::begin() {
    return data;
}

template<typename T>
inline T* SimpleVector<T>::end() {
    return data + size;
}

template<typename T>
inline const T* SimpleVector<T>::begin() const {
    return data;
}

template<typename T>
inline const T* SimpleVector<T>::end() const {
    return data + size;
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

    


}

template<typename T>
inline void SimpleVector<T>::reserve(size_t new_cap) {
    if (new_cap <= capacity) return;
    T* new_data = new T[new_cap];

    for (size_t i = 0; i < size; ++i) {
        new_data[i] = data[i];
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