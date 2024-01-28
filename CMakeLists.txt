cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(3DViewer VERSION 2.0 LANGUAGES CXX C)

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

if(CMAKE_HOST_SYSTEM STREQUAL "Linux")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")
endif()

add_executable(main src/main.cc src/Model/model.cc src/Model/parser.cc src/Model/affine.cc)

include(CTest)
enable_testing()

add_subdirectory(src/tests)

