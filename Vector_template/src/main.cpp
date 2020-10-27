#include <iostream>
#include <string>
#include <cstring>
#include <cassert>

#include "../include/my_vector.h"

using std::swap;

namespace product {

    class Product {
    public:

        Product(const char *name, int quantity, double price) : quantity_(quantity), price_(price) {
            name_ = new char[strlen(name) + 1];
            strcpy(name_, name);
        }

        Product(const Product &other) {
            name_ = new char[strlen(other.name_) + 1];
            strcpy(name_, other.name_);
            price_ = other.price_;
            quantity_ = other.quantity_;
        }

        Product &operator=(const Product &other) {
            if (this != &other) {
                Product tmp_product(other);
                swap(name_, tmp_product.name_);
                swap(price_, tmp_product.price_);
                swap(quantity_, tmp_product.quantity_);
            }
            return *this;
        }

        ~Product() {
            delete[] name_;
        }

        bool operator==(const Product &other) const {
            return (strcmp(name_, other.name_) == 0 && quantity_ == other.quantity_ && price_ == other.price_);
        }

        bool operator!=(const Product &other) const {
            return !(*this == other);
        }

        const char *get_name() const {
            return name_;
        }

        int get_quantity() const {
            return quantity_;
        }

        double get_price() const {
            return price_;
        }

    private:
        char *name_;
        int quantity_;
        double price_;
    };

    std::ostream &operator<<(std::ostream &ost, const Product &prod) {
        ost << std::string(prod.get_name()) << " ";
        ost << prod.get_quantity() << " ";
        ost << prod.get_price();
        return ost;
    }
}

template <typename T>
void test_my_vector (T d1, T d2) {
    try {
        my_vector::my_vector<T> v1;
        my_vector::my_vector<T> v2;
        assert(v1.size() == 0);
        assert(v1.empty());
        assert(v2.size() == 0);
        assert(v1.capacity() == 0);
        assert(v2.capacity() == 0);
        v1.push_back(d2);
        assert(v1[0] == d2);
        v1.push_back(d1);
        assert(v1[1] == d1);
        v2.push_back(d1);
        assert(v2[0] == v1[1]);
        assert(v2[0] == d1);
        assert(v2.size() == 1);
        assert(v2.capacity() == 1);
        v2.pop_back();
        assert(v2.empty());
        assert(v2.capacity() == 1);
        v2.push_back(d2);
        v2[0] = d2;
        assert(v2.size() == 1);
        assert(v2[0] == d2);
        v2 = v1;
        assert(v2.size() == v1.size());
        assert(v2.capacity() == v1.capacity());
        assert(v2[0] == v1[0]);
        assert(v2[1] == v1[1]);
        v1.clear();
        assert(v1.empty());
        my_vector::my_vector<T> v3;
        v3.push_back(d1);
        my_vector::my_vector<T> v4(std::move(v3));
        assert(v4[0] == d1);
        v2.reserve(6);
        assert(v2.capacity() == 8);
        assert(v2[0] == d2);
    } catch (...) {}

    my_vector::my_vector<T> v5;
    v5.push_back(d2);
    try {
        v5[10] = d1;
        assert(false);
    } catch (...) {}

    my_vector::my_vector<T> v6;
    try {
        v6.pop_back();
        assert(false);
    } catch (...) {}
}

template <typename T>
void test_my_vector_default_constructible(T d1, T d2) {
    try {
        my_vector::my_vector<T> v1;
        my_vector::my_vector<T> v2(3);
        assert(v1.size() == 0);
        assert(v1.empty());
        assert(v2.size() == 3);
        assert(v1.capacity() == 0);
        assert(v2.capacity() == 4);
        v1.push_back(d2);
        assert(v1[0] == d2);
        v2.push_back(d1);
        assert(v2[3] == d1);
        assert(v2.size() == 4);
        assert(v2.capacity() == 4);
        v2.push_back(d2);
        assert(v2.size() == 5);
        assert(v2.capacity() == 8);
        v2.resize(3);
        assert(v2.size() == 3);
    } catch (...) {}
}

using namespace product;

int main() {
    test_my_vector<int>(5, 10);
    test_my_vector<Product>(Product("asdf", 4, 12.0), Product("qwe", -1, 7.5));
    test_my_vector_default_constructible(3, 14);
    return 0;
}