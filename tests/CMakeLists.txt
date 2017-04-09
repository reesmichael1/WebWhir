cmake_minimum_required(VERSION 2.6)
project(WebWhirTests CXX)

add_definitions(-std=c++14)

add_subdirectory(layout_tests)
add_subdirectory(htmlparser_tests)
add_subdirectory(loader_tests)

add_library(test_skeleton test_skeleton.cpp)
