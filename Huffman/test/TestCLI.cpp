#include <cstring>
#include "doctest.h"
#include "CLI.h"

TEST_CASE ("class CLI") {
    CLI cli_fir;
    int argc = 6;
    char argv[6][10];
    strcpy(argv[1], "-c");
    strcpy(argv[2], "-f");
    strcpy(argv[3], "in.txt");
    strcpy(argv[4], "-o");
    strcpy(argv[5], "out.bin");
    char *argv_tmp[6];
    for (int i = 0; i < 6; i++) {
        argv_tmp[i] = &argv[i][0];
    }
    cli_fir.parse_args(argc, argv_tmp);
            CHECK(cli_fir.get_operation() == "construct");
            CHECK(cli_fir.get_input() == "in.txt");
            CHECK(cli_fir.get_output() == "out.bin");
}