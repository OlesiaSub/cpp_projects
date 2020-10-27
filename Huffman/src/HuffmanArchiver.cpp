#include <iostream>
#include <unordered_map>
#include <vector>
#include <climits>

#include "HuffmanArchiver.h"

using namespace Huffman;

const int BIT_CNT = 1;

char Archiver::read_symbol() {
    if (bit_cnt_ == 0) {
        is_->read(&data_, BIT_CNT);
        if (is_->bad()) {
            throw ArchiverException();
        }
        bit_cnt_ = CHAR_BIT;
    }
    uint8_t current_bit = (data_ >> (CHAR_BIT - BIT_CNT)) & BIT_CNT;
    data_ = data_ << BIT_CNT;
    bit_cnt_--;
    return current_bit;
}

void Archiver::write_symbol(char current_bit, bool force) {
    if (force) {
        for (int i = 0; i < CHAR_BIT - bit_cnt_; i++) {
            data_ = (data_ << BIT_CNT) | 0;
        }
        os_->write(&data_, BIT_CNT);
        if (os_->bad()) {
            throw ArchiverException();
        }
        return;
    }
    data_ = (data_ << BIT_CNT) | current_bit;
    bit_cnt_++;
    if (bit_cnt_ == CHAR_BIT) {
        os_->write(&data_, BIT_CNT);
        if (os_->bad()) {
            throw ArchiverException();
        }
        bit_cnt_ = 0;
        data_ = 0;
    }
}

void Archiver::compress(std::istream &is, std::ostream &os, HuffmanTree &huffman_tree) {
    Archiver output(os);
    is.clear();
    is.seekg(0, std::istream::beg);
    char symbol;
    while (is.peek() != EOF) {
        is.get(symbol);
        if (is.bad()) {
            throw ArchiverException();
        }
        for (int i = 0; i < (int) huffman_tree.get_code(huffman_tree.get_index(symbol)).size(); i++) {
            output.write_symbol(huffman_tree.get_code(huffman_tree.get_index(symbol))[i], false);
        }
    }
    output.write_symbol(0, true);
}

void Archiver::decompress(std::istream &is, std::ostream &os, HuffmanTree &huffman_tree, int cnt) {
    Archiver input(is);
    int i = 0;
    int SYMBOL_CNT = BIT_CNT;
    std::vector<char> cur_code;
    while (i < cnt) {
        cur_code.clear();
        while (true) {
            char bit = input.read_symbol();
            cur_code.push_back(bit);
            if (huffman_tree.find_code(cur_code)) {
                char cur_symbol[SYMBOL_CNT];
                cur_symbol[0] = huffman_tree.set_code(cur_code);
                os.write((char *) (cur_symbol), sizeof(char));
                if (os.bad()) {
                    throw ArchiverException();
                }
                break;
            }
        }
        i++;
    }
}

void Archiver::encode(std::istream &is, std::ostream &os) {
    HuffmanTree huffman_tree;
    huffman_tree.set_frequencies(is);
    huffman_tree.build_tree();
    char ans[UCHAR_MAX];
    huffman_tree.generate_codes(ans, 0, huffman_tree.get_root());
    huffman_tree.write_frequencies(os);
    Archiver::compress(is, os, huffman_tree);
}

void Archiver::decode(std::istream &is, std::ostream &os) {
    HuffmanTree huffman_tree;
    huffman_tree.get_frequencies(is);
    huffman_tree.build_tree();
    char ans[UCHAR_MAX];
    huffman_tree.generate_codes(ans, 0, huffman_tree.get_root());
    Archiver::decompress(is, os, huffman_tree, huffman_tree.get_symbols_cnt());
}

const char* ArchiverException::what() const noexcept {
    return "Archiving error.";
}

