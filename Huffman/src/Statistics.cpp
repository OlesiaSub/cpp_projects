#include <iostream>
#include <climits>

#include "Statistics.h"

void Statistics::print_statistics(std::iostream &is, std::iostream &os, CLI &cli) {
    is.clear();
    is.seekg(0, std::iostream::end);
    int input_sz = is.tellg();
    is.seekg(0, std::iostream::beg);
    os.clear();
    os.seekg(0, std::iostream::end);
    int output_sz = os.tellp();
    os.seekg(0, std::iostream::beg);
    if (is.bad()) {
        throw StatisticsException();
    }
    if (os.bad()) {
        throw StatisticsException();
    }
    int extra_info = sizeof(int) * UCHAR_MAX + sizeof(char) * UCHAR_MAX;
    if (cli.get_operation() == "construct") {
        std::cout << input_sz << '\n' << output_sz - extra_info << '\n' << extra_info << '\n';
    } else if (cli.get_operation() == "extract") {
        std::cout << input_sz - extra_info << '\n' << output_sz << '\n' << extra_info << '\n';
    }
}

const char* StatisticsException::what() const noexcept {
    return "Error while getting statistics.";
}