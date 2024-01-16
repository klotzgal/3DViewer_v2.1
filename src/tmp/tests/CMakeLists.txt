if (BUILD_TESTING)

  find_package(GTest REQUIRED)

  add_executable(unit_tests test.cc ../../Model/model.cc ../../Model/parser.cc ../../Model/affine.cc)
  
  target_link_libraries(unit_tests matrix GTest::GTest GTest::Main)
  include(GoogleTest)
  gtest_discover_tests(unit_tests)

endif()