#ifndef MY_ARRAY_H_
#define MY_ARRAY_H_

#include <cstddef>
#include <iostream>
#include <cstring>
#include <cassert>
#include <cstdint>

namespace lab_13 {

    template<typename T, size_t N>
    class my_array {
    public:

        constexpr T &operator[](size_t index) noexcept {
            assert(index < N);
            return data_[index];
        }

        constexpr const T &operator[](size_t index) const noexcept {
            assert(index < N);
            return data_[index];
        }

        constexpr T &at(size_t index) {
            if (index < 0 || index >= N) {
                throw std::out_of_range("Index is out of range.\n"); // ?
            }
            return operator[](index);
        }

        constexpr const T &at(size_t index) const {
            if (index < 0 || index >= N) {
                throw std::out_of_range("Index is out of range.\n");
            }
            return operator[](index);
        }

        constexpr bool empty() const noexcept {
            return (N == 0);
        }

        constexpr size_t size() const noexcept {
            return N;
        }

        constexpr void fill(const T &val) noexcept {
            for (int i = 0; i < N; i++) {
                data_[i] = val;
            }
        }

    private:
        T data_[N];
    };

    class proxy {
    public:

        proxy(uint8_t *info, uint8_t index) : info_(info), index_(index) {}

        ~proxy() = default;

        constexpr proxy &operator=(bool cur_bit) noexcept {
            *info_ &= ~(1 << index_);
            *info_ |= (cur_bit) << index_;
            return *this;
        }

        constexpr proxy &operator=(const proxy &px) noexcept {
            *this = bool(px);
            return *this;
        }

        constexpr operator bool() const noexcept {
            return *info_ & (1 << index_);
        }

    private:
        uint8_t *info_;
        uint8_t index_;

        template<typename T, size_t N>
        friend
        class my_array;
    };

    template<size_t N>
    class my_array<bool, N> {

    public:

        constexpr bool operator[](size_t index) const noexcept {
            assert (index < N);
            return (data_[index / CHAR_BIT] >> index % CHAR_BIT) & 1;
        }

        proxy operator[](size_t index) noexcept {
            assert(index < N);
            return proxy(&data_[index / CHAR_BIT], index % CHAR_BIT);
        }

        constexpr bool at(size_t index) const {
            if (index < 0 || index >= N)
                throw std::out_of_range("Index is out of range.\n");
            return operator[](index);
        }

        proxy at(size_t index) {
            if (index < 0 || index >= N)
                throw std::out_of_range("Index is out of range.\n");
            return operator[](index);
        }

        constexpr bool empty() const noexcept {
            return (N == 0);
        }

        constexpr size_t size() const noexcept {
            return N;
        }

        void fill(bool val) {
            int new_val = (val ? ~0 : 0);
            for (int i = 0; i < capacity_; i++) {
                data_[i] = new_val;
            }
        }

    private:
        static const int8_t capacity_ = N / CHAR_BIT + (N % CHAR_BIT ? 1 : 0);
        uint8_t data_[capacity_];
    };

}  // namespace lab_13

#endif  // MY_ARRAY_H_
