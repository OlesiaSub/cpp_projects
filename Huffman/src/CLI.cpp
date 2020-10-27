#include <cstring>
#include "CLI.h"

void CLI::parse_args(int argc, char ** argv) {
    for (int i = 1; i < argc; i++) {
        std::string_view arg = argv[i];
        if (arg == "-c") {
            operation = "construct";
        } else if (arg == "-u") {
            if (operation == "construct") {
                throw ArgumentException();
            }
            operation = "extract";
        } else if (arg == "-f" or arg == "--input") {
            i++;
            input = argv[i];
        } else if (arg == "-o" or arg == "--output") {
            i++;
            output = argv[i];
        } else {
            throw ArgumentException();
        }
    }
    if (operation != "construct" and operation != "extract") {
        throw ArgumentException();
    }
    if (input.empty()) {
        throw ArgumentException();
    }
    if (output.empty()) {
        throw ArgumentException();
    }
}

const char* ArgumentException::what() const noexcept {
    return "Error while parsing arguments.";
}