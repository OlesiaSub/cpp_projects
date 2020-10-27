#include <iostream>
#include <fstream>

#include "HuffmanArchiver.h"
#include "CLI.h"

using namespace Huffman;

int main(int argc, char *argv[]) {
    std::fstream ifs;
    std::fstream ofs;

    CLI commands;
    try {
        commands.parse_args(argc, argv);
    } catch (ArgumentException &ex) {
        std::cout << ex.what() << '\n';
        return 1;
    }
    try {
        ifs = std::fstream(commands.get_input(), std::ios::in | std::ios_base::binary);

        if (ifs.peek() == EOF) {
            std::cout << 0 << '\n' << 0 << '\n' << 0 << '\n';
            return 0;
        }

        if (ifs.bad()) {
            throw ArchiverException();
        }

        ofs = std::fstream(commands.get_output(), std::ios::out | std::ios_base::binary);

        if (ofs.bad()) {
            throw ArchiverException();
        }

        if (commands.get_operation() == "construct") {
            Archiver::encode(ifs, ofs);
        } else if (commands.get_operation() == "extract") {
            Archiver::decode(ifs, ofs);
        }

        Statistics::print_statistics(ifs, ofs, commands);
    } catch (const std::exception ex) {
        std::cout << ex.what() << '\n';
    }
}