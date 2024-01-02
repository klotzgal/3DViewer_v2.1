cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(3DViewer2.0 CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -g -Wall -Wextra -Werror -fopenmp")
add_library(matrix STATIC Matrix/s21_matrix_oop.cc)
add_executable(main main.cc Model/model.cc Model/parser.cc)
target_link_libraries(main matrix)


