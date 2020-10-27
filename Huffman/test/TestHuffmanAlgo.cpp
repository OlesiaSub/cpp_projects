#include "doctest.h"
#include "Huffman.h"
#include <sstream>
#include <climits>

using namespace Huffman;

TEST_CASE ("HuffmanTree write_frequencies") {
    std::vector<int> freq(UCHAR_MAX);
    std::fill(freq.begin(), freq.end(), 0);
    std::vector<char> idx(UCHAR_MAX);
    std::fill(idx.begin(), idx.end(), '0');
    std::string in_data = "hello, world, i hate writing tests!)!";
    for (char i : in_data) {
        freq[static_cast<int>(i)]++;
        idx[static_cast<int>(i)] = i;
    }
    std::stringstream strm;
    strm.write((char *) freq.data(), sizeof(int) * UCHAR_MAX);
    strm.write((char *) idx.data(), sizeof(char) * UCHAR_MAX);
    HuffmanTree tree;
    tree.get_frequencies(strm);
    std::stringstream result;
    tree.write_frequencies(result);
            CHECK(strm.str() == result.str());
}

TEST_CASE ("HuffmanTree get_frequencies") {
    std::vector<int> freq(UCHAR_MAX);
    std::fill(freq.begin(), freq.end(), 0);
    std::vector<char> idx(UCHAR_MAX);
    std::fill(idx.begin(), idx.end(), '0');
    std::stringstream strm;
    strm.write((char *) freq.data(), sizeof(int) * UCHAR_MAX);
    strm.write((char *) idx.data(), sizeof(char) * UCHAR_MAX);
    HuffmanTree tree;
    tree.get_frequencies(strm);

    for (int i = 0; i < (int)freq.size(); i++) {
                CHECK(freq[i] == tree.get_frequency(i));
    }
    for (int i = 0; i < (int)idx.size(); i++) {
                CHECK(idx[i] == tree.get_index(i));
    }
}

TEST_CASE ("Huffman tree set_frequencies") {
    std::vector<int> freq(UCHAR_MAX);
    std::fill(freq.begin(), freq.end(), 0);
    std::vector<char> idx(UCHAR_MAX);
    std::fill(idx.begin(), idx.end(), 0);
    std::string in_data = "hello ym dear friendssss";
    for (char i : in_data) {
        freq[(int) i]++;
        idx[(int) i] = i;
    }
    std::stringstream strm(in_data);
    HuffmanTree tree;
    tree.set_frequencies(strm);

    for (int i = 0; i < (int)freq.size(); i++) {
                CHECK(freq[i] == tree.get_frequency(i));
    }
    for (int i = 0; i < (int)idx.size(); i++) {
                CHECK(idx[i] == tree.get_index(i));
    }
}

TEST_CASE ("HuffmanTree generate_codes") {
    HuffmanTree tree;
    char ans[UCHAR_MAX];
    std::map<uint8_t, std::vector<char>> codes;
    std::string in_data = "HIHIHIHIIIIII";
    std::vector<char> a(1);
    a[0] = 0;
    codes[72] = a;
    std::vector<char> b(1);
    b[0] = 1;
    codes[73] = b;
    std::stringstream strm(in_data);
    tree.set_frequencies(strm);
    tree.build_tree();
    tree.generate_codes(ans, 0, tree.get_root());
            CHECK(codes[72] == tree.get_code(72));
            CHECK(codes[73] == tree.get_code(73));
            CHECK(codes[218] == tree.get_code(218));
}