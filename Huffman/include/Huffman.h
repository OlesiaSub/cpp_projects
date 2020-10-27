#ifndef HW_03_HUFFMAN_H
#define HW_03_HUFFMAN_H

#include <iostream>
#include <utility>
#include <vector>
#include <queue>
#include <map>
#include <unordered_map>
#include <memory>
#include <climits>

namespace Huffman {

    class HuffmanTree {
    private:
        class HuffmanNode {
        public:
            HuffmanNode() : data_(' '), frequency_(0), left_(nullptr), right_(nullptr) {}

            HuffmanNode(char data, int frequency) : data_(data), frequency_(frequency), left_(nullptr),
                                                    right_(nullptr) {}

            ~HuffmanNode() = default;

            bool operator<(const std::unique_ptr<HuffmanNode> &a) const;

            inline int get_node_frequency() const {
                return frequency_;
            }

            struct compare {
                inline bool operator()(const std::unique_ptr<HuffmanNode> &a, const std::unique_ptr<HuffmanNode> &b) {
                    return a->get_node_frequency() < b->get_node_frequency();
                }
            };

        private:
            char data_;
            int frequency_;
            std::unique_ptr<HuffmanNode> left_;
            std::unique_ptr<HuffmanNode> right_;

            friend class HuffmanTree;
        };

        int symbols_cnt_ = 0;
        std::unique_ptr<HuffmanNode> tree_root;
        std::map<uint8_t, std::vector<char>> symbol_codes_;
        std::vector<int> symbol_frequencies_;
        std::vector<char> symbol_indexes_;
        std::vector<std::unique_ptr<HuffmanNode>> huffman_tree_init_;
        std::queue<std::unique_ptr<HuffmanNode>> huffman_queue_first_;
        std::queue<std::unique_ptr<HuffmanNode>> huffman_queue_second_;
        //std::priority_queue<std::unique_ptr<HuffmanNode>, std::vector<std::unique_ptr<HuffmanNode>>> huffman_pq_;
        std::map<std::vector<char>, char> symbol_codes_reversed_;

    public:
        HuffmanTree() {
            symbol_frequencies_.resize(UCHAR_MAX);
            symbol_indexes_.resize(UCHAR_MAX);
        }

        ~HuffmanTree() = default;

        void build_tree();

        void generate_codes(char ans[], int up, std::unique_ptr<HuffmanNode> parent = nullptr);

        void set_frequencies(std::istream &is);

        void get_frequencies(std::istream &is);

        void write_frequencies(std::ostream &os);

        char set_code(const std::vector<char> &code);

        bool find_code(const std::vector<char> &code);

        inline int get_symbols_cnt() {
            return symbols_cnt_;
        }

        std::unique_ptr<HuffmanNode> get_root() {
            return std::move(tree_root);
        }

        inline std::vector<char> get_code(uint8_t i) {
            return symbol_codes_[i];
        }

        inline int get_frequency(int i) {
            return symbol_frequencies_[i];
        }

        inline char get_index(int i) {
            return symbol_indexes_[i];
        }
    };

    class CompressingException : std::exception {
    public:
        const char* what() const throw();
    };

    class DecompressingException : std::exception {
    public:
        const char* what() const throw();
    };

}

#endif