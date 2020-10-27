#ifndef MY_VECTOR_H_
#define MY_VECTOR_H_

#include <cstddef>
#include <iostream>

namespace my_vector {

    template<class T>
    class my_vector {
    public:
        explicit my_vector() noexcept;
        explicit my_vector(size_t n);
        my_vector(const my_vector& other);
        my_vector(my_vector&& other) noexcept;
        my_vector& operator=(const my_vector& other);
        my_vector& operator=(my_vector&& other) noexcept;
        ~my_vector();

        size_t size() const noexcept;
        size_t capacity() const noexcept;
        bool empty() const noexcept;

        void resize(size_t n);
        void reserve(size_t n);

        const T& operator[](int idx) const;
        T& operator[](int idx);

        void push_back(T t);
        void pop_back();
        void clear();

        static size_t incr_size(size_t x);

    private:
        size_t capacity_;
        size_t size_;
        T* array_;
    };
}

#include "my_vector_impl.h"

#endif  // MY_VECTOR_H_