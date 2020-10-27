#ifndef LAB_12_MY_VECTOR_IMPL_H
#define LAB_12_MY_VECTOR_IMPL_H

#include <iostream>
#include <algorithm>
#include "my_vector.h"

template <typename T>
std::ostream& operator<<(std::ostream& os, const my_vector::my_vector<T>& data) {
    for (size_t i = 0; i < data.size(); i++) {
        if (i == data.size() - 1) {
            os << data[i];
        } else {
            os << data[i] << ' ';
        }
    }
    return os;
}

template <typename T>
my_vector::my_vector<T>::my_vector() noexcept {
    capacity_ = 0;
    size_ = 0;
    array_ = nullptr;
}

template <typename T>
my_vector::my_vector<T>::my_vector(size_t n) : my_vector() {
    resize(n);
}

template <typename T>
my_vector::my_vector<T>::my_vector(const my_vector& other) : my_vector() {
    reserve(other.capacity_);
    size_ = other.size_;
    for (size_t i = 0; i < size_; i++) {
        new(array_ + i) T(other[i]);
    }
}

template <typename T>
my_vector::my_vector<T>::my_vector(my_vector&& other) noexcept : my_vector() {
    my_vector<T> tmp_arr(other);
    *this = std::move(tmp_arr);
}

template <typename T>
my_vector::my_vector<T>& my_vector::my_vector<T>::operator=(const my_vector& other) {
    if (this != &other) {
        my_vector <T> tmp_arr(other);
        *this = std::move(tmp_arr);
    }
    return *this;
}

template <typename T>
my_vector::my_vector<T>& my_vector::my_vector<T>::operator=(my_vector&& other) noexcept {
    if (this != &other) {
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
        std::swap(array_, other.array_);
    }
    return *this;
}

template <typename T>
my_vector::my_vector<T>::~my_vector() {
    for (size_t i = 0; i < size_; i++) {
        array_[i].~T();
    }
    delete [] reinterpret_cast<char*>(array_);
}

template <typename T>
size_t my_vector::my_vector<T>::size() const noexcept {
    return size_;
}

template <typename T>
size_t my_vector::my_vector<T>::capacity() const noexcept {
    return capacity_;
}

template <typename T>
bool my_vector::my_vector<T>::empty() const noexcept {
    return (size_ == 0);
}

template <typename T>
void my_vector::my_vector<T>::resize(size_t n) {
    reserve(n);
    if (n < size_) {
        for (size_t i = n; i < size_; i++) {
            array_[i].~T();
        }
    }
    else {
        for (size_t i = size_; i < n; i++) {
            new (array_ + i) T();
        }
    }
    size_ = n;
}

template <typename T>
void my_vector::my_vector<T>::reserve(size_t n) {
    if (n <= capacity_)
        return;
    capacity_ = incr_size(n);
    T* tmp_arr = reinterpret_cast<T *>(new char[capacity_ * sizeof(T)]);
    for (size_t i = 0; i < size_; i++) {
        new (tmp_arr + i) T(array_[i]);
    }
    for (int i = 0; i < size_; i++) {
        array_[i].~T();
    }
    delete [] reinterpret_cast<char*>(array_);
    array_ = tmp_arr;
}

template <typename T>
const T& my_vector::my_vector<T>::operator[](int idx) const {
    if (idx >= size_ || idx < 0) {
        throw std::range_error("Index is not available.\n");
    }
    return reinterpret_cast<T*>(array_)[idx];
}

template <typename T>
T& my_vector::my_vector<T>::operator[](int idx) {
    if (idx >= size_ || idx < 0) {
        throw std::range_error("Index is not available.\n");
    }
    return reinterpret_cast<T*>(array_)[idx];
}

template <typename T>
void my_vector::my_vector<T>::push_back(T t) {
    if (size_ == capacity_) {
        reserve(size_ + 1);
    }
    new (array_ + size_) T(t);
    size_++;
}

template <typename T>
void my_vector::my_vector<T>::pop_back() {
    if (empty()) {
        throw std::logic_error("Size is too small.\n");
    }
    size_--;
    array_[size_].~T();
}

template <typename T>
void my_vector::my_vector<T>::clear() {
    for (size_t i = 0; i < size_; i++) {
        array_[i].~T();
    }
    size_ = 0;
}

template<class T>
size_t my_vector::my_vector<T>::incr_size(size_t x) {
    size_t res = 1;
    while (res < x) {
        res *= 2;
    }
    return res;
}

#endif //LAB_12_MY_VECTOR_IMPL_H
