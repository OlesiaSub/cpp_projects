#include <vector>
#include <algorithm>
#include <unordered_map>
#include <climits>

#include "Huffman.h"

using namespace Huffman;

bool HuffmanTree::HuffmanNode::operator<(const std::unique_ptr<HuffmanNode> &a) const {
    return this->frequency_ < a->get_node_frequency();
}


void HuffmanTree::build_tree() {
    for (int i = 0; i < UCHAR_MAX; i++) {
        if (symbol_frequencies_[i] > 0) {
            std::unique_ptr<HuffmanNode> node = std::make_unique<HuffmanNode>(symbol_indexes_[i],
                                                                              symbol_frequencies_[i]);
            huffman_tree_init_.push_back(std::move(node));
        }
    }
    std::sort(huffman_tree_init_.begin(), huffman_tree_init_.end(), HuffmanNode::compare());
    for (auto &i : huffman_tree_init_) {
        std::unique_ptr<HuffmanNode> elem = std::make_unique<HuffmanNode>();
        elem = std::move(i);
        huffman_queue_first_.emplace(std::move(elem));
    }
    while (true) {
        std::unique_ptr<HuffmanNode> node_fir = std::make_unique<HuffmanNode>();
        std::unique_ptr<HuffmanNode> node_sec = std::make_unique<HuffmanNode>();
        if (huffman_queue_second_.empty() and huffman_queue_first_.empty()) {
            break;
        }
        if (huffman_queue_first_.size() == 1 and huffman_queue_second_.empty()) {
            tree_root = std::move(huffman_queue_first_.front());
            break;
        }
        if (huffman_queue_second_.empty()) {
            if (huffman_queue_first_.size() == 1) {
                tree_root = std::move(huffman_queue_first_.front());
                break;
            } else {
                node_fir = std::move(huffman_queue_first_.front());
                huffman_queue_first_.pop();
                node_sec = std::move(huffman_queue_first_.front());
                huffman_queue_first_.pop();
            }
        } else if (huffman_queue_first_.empty()) {
            if (huffman_queue_second_.size() == 1) {
                tree_root = std::move(huffman_queue_second_.front());
                break;
            } else {
                node_fir = std::move(huffman_queue_second_.front());
                huffman_queue_second_.pop();
                node_sec = std::move(huffman_queue_second_.front());
                huffman_queue_second_.pop();
            }
        } else {
            if (huffman_queue_second_.front()->operator<(huffman_queue_first_.front())) {
                node_fir = std::move(huffman_queue_second_.front());
                huffman_queue_second_.pop();
            } else {
                node_fir = std::move(huffman_queue_first_.front());
                huffman_queue_first_.pop();
            }
            if (!huffman_queue_second_.empty() and !huffman_queue_first_.empty()) {
                if (huffman_queue_second_.front()->operator<(huffman_queue_first_.front())) {
                    node_sec = std::move(huffman_queue_second_.front());
                    huffman_queue_second_.pop();
                } else {
                    node_sec = std::move(huffman_queue_first_.front());
                    huffman_queue_first_.pop();
                }
            } else if (huffman_queue_first_.empty()) {
                node_sec = std::move(huffman_queue_second_.front());
                huffman_queue_second_.pop();
            } else if (huffman_queue_second_.empty()) {
                node_sec = std::move(huffman_queue_first_.front());
                huffman_queue_first_.pop();
            }
        }
        std::unique_ptr<HuffmanNode> new_node = std::make_unique<HuffmanNode>();
        new_node->frequency_ = node_fir->get_node_frequency() + node_sec->get_node_frequency();
        new_node->data_ = '~';
        new_node->left_ = std::move(node_fir);
        new_node->right_ = std::move(node_sec);
        huffman_queue_second_.emplace(std::move(new_node));
        if (huffman_queue_first_.size() + huffman_queue_second_.size() < 1) {
            tree_root = std::move(new_node);
            break;
        }
    }
}

void HuffmanTree::generate_codes(char answer[], int nxt, std::unique_ptr<HuffmanNode> parent) {
    if (huffman_queue_second_.empty() and huffman_queue_first_.empty()) return;
    if (huffman_queue_first_.size() == 1 and huffman_queue_second_.empty()) {
        std::vector<char> cur_answer(1);
        cur_answer[0] = 0;
        symbol_codes_[symbol_indexes_[parent->data_]] = cur_answer;
        symbol_codes_reversed_[cur_answer] = parent->data_;
    }
    if (parent->left_) {
        answer[nxt] = 0;
        generate_codes(answer, nxt + 1, std::move(parent->left_));
    }
    if (parent->right_) {
        answer[nxt] = 1;
        generate_codes(answer, nxt + 1, std::move(parent->right_));
    }
    if (parent->data_ != '~') {
        std::vector<char> cur_answer;
        cur_answer.reserve(nxt);
        for (int i = 0; i < nxt; i++) {
            cur_answer.push_back((char) answer[i]);
        }
        symbol_codes_[symbol_indexes_[parent->data_]] = cur_answer;
        symbol_codes_reversed_[cur_answer] = parent->data_;
    }
}

void HuffmanTree::set_frequencies(std::istream &is) {
    symbol_frequencies_.resize(UCHAR_MAX);
    symbol_indexes_.resize(UCHAR_MAX);
    std::fill(symbol_frequencies_.begin(), symbol_frequencies_.end(), 0);
    std::fill(symbol_indexes_.begin(), symbol_indexes_.end(), 0);
    if (!is) {
        throw CompressingException();
    }
    char symbol;
    while (is.peek() != EOF) {
        is.get(symbol);
        if (is.bad()) {
            throw CompressingException();
        }
        symbol_frequencies_[static_cast<int>(symbol)]++;
        symbol_indexes_[static_cast<int>(symbol)] = symbol;
    }
}

void HuffmanTree::get_frequencies(std::istream &is) {
    symbol_frequencies_.resize(UCHAR_MAX);
    symbol_indexes_.resize(UCHAR_MAX);
    is.read((char *) symbol_frequencies_.data(), sizeof(int) * UCHAR_MAX);
    for (int i =0; i < UCHAR_MAX; i++) {
        symbols_cnt_ += symbol_frequencies_[i];
    }
    is.read((char *) symbol_indexes_.data(), sizeof(char) * UCHAR_MAX);
    if (is.bad()) {
        throw DecompressingException();
    }
}

void HuffmanTree::write_frequencies(std::ostream &os) {
    os.write((char *) symbol_frequencies_.data(), sizeof(int) * UCHAR_MAX);
    os.write((char *) symbol_indexes_.data(), sizeof(char) * UCHAR_MAX);
    if (os.bad()) {
        throw CompressingException();
    }
}

char HuffmanTree::set_code(const std::vector<char>& code) {
    std::map<std::vector<char>, char>::iterator it;
    it = symbol_codes_reversed_.find(code);
    if (it != symbol_codes_reversed_.end()) {
        return it->second;
    }
    return 0;
}

bool HuffmanTree::find_code(const std::vector<char>& code) {
    std::map<std::vector<char>, char>::iterator it;
    it = symbol_codes_reversed_.find(code);
    return it != symbol_codes_reversed_.end();
}

const char* CompressingException::what() const noexcept {
    return "Compressing error.";
}

const char* DecompressingException::what() const noexcept {
    return "Decompressing error.";
}