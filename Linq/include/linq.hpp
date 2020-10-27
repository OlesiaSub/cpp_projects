#ifndef LINQ_H_
#define LINQ_H_

#include <utility>
#include <vector>
#include <iterator>
#include <functional>

namespace linq {
    namespace impl {

        template<typename T, typename Iter>
        class range_enumerator;

        template<typename T>
        class drop_enumerator;

        template<typename T, typename U, typename F>
        class select_enumerator;

        template<typename T, typename F>
        class until_enumerator;

        template<typename T>
        class take_enumerator;

        template<typename T, typename F>
        class where_enumerator;

        template<typename T>
        class enumerator {
        public:
            virtual const T &operator*() const = 0;

            virtual void operator++() = 0;

            virtual operator bool() const noexcept = 0;

            auto drop(int count) {
                return drop_enumerator<T>(*this, count);
            }

            auto take(int count) {
                return take_enumerator<T>(*this, count);
            }

            template<typename U = T, typename F>
            auto select(F func) {
                return select_enumerator<U, T, F>(*this, std::move(func));
            }

            template<typename F>
            auto until(F func) {
                return until_enumerator<T, F>(*this, std::move(func));
            }

            auto until_eq(const T &obj_fir) {
                auto func = [&obj_fir](const T &obj_sec) { return obj_fir == obj_sec; };
                return until(func);
            }

            template<typename F>
            auto where(F func) {
                return where_enumerator<T, F>(*this, std::move(func));
            }

            auto where_neq(const T &obj_fir) {
                auto func = [obj_fir](const T &obj_sec) { return obj_fir != obj_sec; };
                return where(func);
            }

            std::vector<T> to_vector() {
                std::vector<T> result;
                this->copy_to(std::back_inserter(result));
                return result;
            }

            template<typename Iter>
            void copy_to(Iter it) {
                while (*this) {
                    *it = (*(*this));
                    ++it;
                    ++(*this);
                }
            }
        };

        template<typename T, typename Iter>
        class range_enumerator : public enumerator<T> {
        public:
            range_enumerator(Iter begin, Iter end) : begin_(begin), end_(end) {}

            const T &operator*() const override {
                return *begin_;
            }

            void operator++() override {
                ++begin_;
            }

            operator bool() const noexcept override {
                return begin_ != end_;
            }

        private:
            Iter begin_, end_;
        };

        template<typename T>
        class drop_enumerator : public enumerator<T> {
        public:
            drop_enumerator(enumerator<T> &parent, int count) : parent_(parent) {
                while (parent_ and count) {
                    ++parent_, --count;
                }
            }

            const T &operator*() const override {
                return *parent_;
            }

            void operator++() override {
                ++parent_;
            }

            operator bool() const noexcept override {
                return static_cast<bool>(parent_);
            }

        private:
            enumerator<T> &parent_;
        };

        template<typename T, typename U, typename F>
        class select_enumerator : public enumerator<T> {
        public:
            select_enumerator(enumerator<U> &parent, F func) : parent_(parent), func_(std::move(func)) {
                if (parent_)
                    object_ = func_(*parent_);
            }

            const T &operator*() const override {
                return object_;
            }

            void operator++() override {
                ++parent_;
                if (parent_)
                    object_ = func_(*parent_);
            }

            operator bool() const noexcept override {
                return static_cast<bool>(parent_);
            }

        private:
            enumerator<U> &parent_;
            F func_;
            T object_;
        };

        template<typename T, typename F>
        class until_enumerator : public enumerator<T> {
        public:
            until_enumerator(enumerator<T> &parent, F func) : parent_(parent), func_(std::move(func)) {
                cur_validity_ = parent_ ? (func_(*parent_) ? false : true) : false;
            }

            const T &operator*() const override {
                return *parent_;
            }

            void operator++() override {
                ++parent_;
                cur_validity_ = parent_ ? (func_(*parent_) ? false : true) : false;
            }

            operator bool() const noexcept override {
                return cur_validity_;
            }

        private:
            enumerator<T> &parent_;
            F func_;
            bool cur_validity_;
        };

        template<typename T, typename F>
        class where_enumerator : public enumerator<T> {
        public:
            where_enumerator(enumerator<T> &parent, F func) : parent_(parent), func_(std::move(func)) {
                while (parent_) {
                    cur_validity_ = func_(*parent_);
                    if (cur_validity_) break;
                    ++parent_;
                }
            }

            const T &operator*() const override {
                return *parent_;
            }

            void operator++() override {
                ++parent_;
                cur_validity_ = false;
                while (parent_) {
                    cur_validity_ = func_(*parent_);
                    if (cur_validity_) break;
                    ++parent_;
                }
            }

            operator bool() const noexcept override {
                return cur_validity_;
            }

        private:
            enumerator<T> &parent_;
            F func_;
            bool cur_validity_ = false;
        };

        template<typename T>
        class take_enumerator : public enumerator<T> {
        public:
            take_enumerator(enumerator<T> &parent, int count) : parent_(parent), count_(count) {}

            const T &operator*() const override {
                return *parent_;
            }

            void operator++() override {
                ++parent_, --count_;
            }

            operator bool() const noexcept override {
                return count_ and parent_;
            }

        private:
            enumerator<T> &parent_;
            int count_;
        };
    } // namespace impl

    template<typename T>
    auto from(T begin, T end) {
        return impl::range_enumerator<typename std::iterator_traits<T>::value_type, T>(begin, end);
    }

} // namespace linq

#endif