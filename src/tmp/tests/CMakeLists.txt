find_package(GTest REQUIRED)

add_executable(unit_tests test.cc ../../Model/model.cc ../../Model/parser.cc ../../Model/affine.cc)
# add_library(matrix STATIC ../../Libs/s21_matrix_oop.cc)

target_link_libraries(unit_tests matrix GTest::GTest GTest::Main)

add_custom_target(test COMMAND ./bin/unit_tests)