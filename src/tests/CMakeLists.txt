# if (BUILD_TESTING)

cmake_minimum_required(VERSION 3.5)

project(test VERSION 1.0 LANGUAGES CXX)
SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY
        ${PROJECT_BINARY_DIR}/bin
        CACHE PATH
        "Single Directory for all"
    )

  add_executable(unit_tests test.cc ../Model/model.cc ../Model/parser.cc ../Model/affine.cc)
  
  include(FetchContent)
  FetchContent_Declare(
    gtest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.13.0
  )
  
  FetchContent_MakeAvailable(gtest)
  include(CTest)
  enable_testing() 
  target_link_libraries(unit_tests GTest::gtest_main)
  include(GoogleTest)
  gtest_discover_tests(unit_tests)
 

# endif()

