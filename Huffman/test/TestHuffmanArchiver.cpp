#include <fstream>
#include <sstream>
#include "doctest.h"
#include "HuffmanArchiver.h"

using namespace Huffman;

TEST_CASE ("class Archiver, extract") {
    std::ifstream is;
    std::ofstream os;
    Archiver huff_exrt(os);
            CHECK(huff_exrt.get_data() == 0);
            CHECK(huff_exrt.get_bit_cnt() == 0);
}

TEST_CASE ("class Archiver, encode and decode, one word") {
    std::stringstream input;
    input << "hello";
    std::stringstream bin_output;
    std::stringstream txt_output;
    Archiver::encode(input, bin_output);
    Archiver::decode(bin_output, txt_output);
    CHECK(input.str() == txt_output.str());
}

TEST_CASE ("class Archiver, encode and decode, random symbols") {
    std::stringstream input;
    input << "hello, world and random symbols $%$*035  39rb32 ofe!!!";
    std::stringstream bin_output;
    std::stringstream txt_output;
    Archiver::encode(input, bin_output);
    Archiver::decode(bin_output, txt_output);
            CHECK(input.str() == txt_output.str());
}

TEST_CASE ("class Archiver, encode and decode, one symbol") {
    std::stringstream input;
    input << "fffffffffffffffffffffffffffffffffffffffffff";
    std::stringstream bin_output;
    std::stringstream txt_output;
    Archiver::encode(input, bin_output);
    Archiver::decode(bin_output, txt_output);
            CHECK(input.str() == txt_output.str());
}