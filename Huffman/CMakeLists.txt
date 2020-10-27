cmake_minimum_required(VERSION 3.5)
project(hw_03)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-O2)

include_directories(include/)
add_executable(hw_03 src/main.cpp src/Huffman.cpp src/HuffmanArchiver.cpp src/CLI.cpp
        include/HuffmanArchiver.h include/CLI.h include/Huffman.h include/Statistics.h src/Statistics.cpp)
add_executable(test_hw_03 test/TestMain.cpp test/doctest.h test/TestCLI.cpp test/TestHuffmanAlgo.cpp test/TestStatistics.cpp test/TestHuffmanArchiver.cpp
        src/Huffman.cpp src/HuffmanArchiver.cpp src/CLI.cpp
        include/HuffmanArchiver.h include/CLI.h include/Huffman.h include/Statistics.h src/Statistics.cpp)
