if (BUILD_TESTING)

  # find_package(GTest REQUIRED)

  add_executable(unit_tests test.cc ../Model/model.cc ../Model/parser.cc ../Model/affine.cc)
  
  include(FetchContent)
  FetchContent_Declare(
    gtest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.13.0
  )
  
  FetchContent_MakeAvailable(gtest)

  target_link_libraries(unit_tests matrix GTest::gtest_main)
  include(GoogleTest)
  gtest_discover_tests(unit_tests)

endif()