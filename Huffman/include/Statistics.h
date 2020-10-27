#ifndef HW_03_STATISTICS_H
#define HW_03_STATISTICS_H

#include <iostream>
#include <exception>

#include "CLI.h"

class Statistics {
private:
    friend class CLI;

public:
    static void print_statistics(std::iostream &is, std::iostream &os, class CLI &cli);
};

class StatisticsException : std::exception {
public:
    const char* what() const throw();
};

#endif