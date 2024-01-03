cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(3DViewer2.0 CXX)

set (CMAKE_CXX_FLAGS 
        "${CMAKE_CXX_FLAGS} -std=c++17 -g -Wall -Wextra -Werror"
    )
    
SET (CMAKE_LIBRARY_OUTPUT_DIRECTORY
        ${PROJECT_BINARY_DIR}/bin
        CACHE PATH
        "Single Directory for all"
    )

SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY
        ${PROJECT_BINARY_DIR}/bin
        CACHE PATH
        "Single Directory for all"
    )

SET (CMAKE_ARCHIVE_OUTPUT_DIRECTORY
        ${PROJECT_BINARY_DIR}/lib
        CACHE PATH
        "Single Directory for all"
    )

# if(CMAKE_HOST_SYSTEM STREQUAL "Linux")
#   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")
# endif()

add_library(matrix STATIC Libs/s21_matrix_oop.cc)
add_executable(main main.cc Model/model.cc Model/parser.cc)
target_link_libraries(main matrix)


