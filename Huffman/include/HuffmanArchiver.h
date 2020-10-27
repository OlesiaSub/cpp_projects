#ifndef HW_03_HUFFMAN_ARCHIVER_H
#define HW_03_HUFFMAN_ARCHIVER_H

#include <iostream>
#include <exception>
#include "Huffman.h"

using Huffman::HuffmanTree;

namespace Huffman {

    class Archiver {
    public:
        explicit Archiver(std::istream &is) : is_(&is), bit_cnt_(0), data_(0) {}

        explicit Archiver(std::ostream &os) : os_(&os), bit_cnt_(0), data_(0) {}

        static void compress(std::istream &is, std::ostream &os, HuffmanTree &huffman_tree);

        static void decompress(std::istream &is, std::ostream &os, HuffmanTree &huffman_tree, int cnt);

        char read_symbol();

        void write_symbol(char current_bit, bool force);

        static void encode(std::istream &is, std::ostream &os);

        static void decode(std::istream &is, std::ostream &os);

        char get_data() {
            return data_;
        }

        uint8_t get_bit_cnt() {
            return bit_cnt_;
        }

    private:
        std::istream *is_{};
        std::ostream *os_{};
        uint8_t bit_cnt_ = 0;
        char data_ = 0;
    };

    class ArchiverException : std::exception {
    public:
        const char* what() const noexcept ;
    };
}

#endif