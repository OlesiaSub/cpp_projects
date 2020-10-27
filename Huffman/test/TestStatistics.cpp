#include <sstream>
#include <cstring>
#include "doctest.h"
#include "CLI.h"
#include "Statistics.h"

const int ALPHABET_SIZE = 255;

TEST_CASE("class Statistics") {
    std::stringstream inputFile("Hello world.");
    std::stringstream outputFile;
    std::string frequency(sizeof(int) * ALPHABET_SIZE, '0');
    std::string idx(sizeof(char) * ALPHABET_SIZE, '0');
    CLI cli;
    int argc_fir = 6;
    char argv_fir[6][10];
    strcpy(argv_fir[1], "-c");
    strcpy(argv_fir[2], "-f");
    strcpy(argv_fir[3], "in.txt");
    strcpy(argv_fir[4], "-o");
    strcpy(argv_fir[5], "out.bin");
    char *argv_fir_tmp[6];
    for (int i = 0; i < 6; i++) {
        argv_fir_tmp[i] = &argv_fir[i][0];
    }
    cli.parse_args(argc_fir, argv_fir_tmp);

    outputFile.write(frequency.c_str(), frequency.size());
    outputFile.write(idx.c_str(), idx.size());
    outputFile << "%binary%";

    std::stringstream stringStream;
    std::streambuf *stdoutBuffer = std::cout.rdbuf();
    std::cout.rdbuf(stringStream.rdbuf());
    Statistics::print_statistics(inputFile, outputFile, cli);
    std::cout.rdbuf(stdoutBuffer);

    int extra = sizeof(int) * ALPHABET_SIZE + sizeof(char) * ALPHABET_SIZE;
    CHECK(stringStream.str() == "12\n8\n" + std::to_string(extra) + '\n');
}