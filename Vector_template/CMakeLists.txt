cmake_minimum_required(VERSION 3.5)
project(lab_12)

set(CMAKE_CXX_STANDARD 17)

include_directories(include/)
add_executable(lab_12 src/main.cpp include/my_vector.h include/my_vector_impl.h)
