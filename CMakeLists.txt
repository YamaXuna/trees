cmake_minimum_required(VERSION 3.24)
project(trees)
include_directories(.)

set(CMAKE_CXX_STANDARD 23)

add_executable(trees tree/tree.h tests/tree_test.cpp)
