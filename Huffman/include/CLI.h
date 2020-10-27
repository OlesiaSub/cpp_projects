#ifndef HW_03_CLI_H
#define HW_03_CLI_H

#include <iostream>
#include "Statistics.h"

class CLI {
public:
    CLI() : operation(""), input(""), output("") {}

    void parse_args(int argc, char **argv);

    inline std::string get_operation() {
        return operation;
    }

    inline std::string get_input() {
        return input;
    }

    inline std::string get_output() {
        return output;
    }

private:
    std::string operation;
    std::string input;
    std::string output;
};

class ArgumentException : std::exception {
public:
    const char* what() const throw();
};


#endif