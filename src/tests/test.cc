#include <gtest/gtest.h>

#include <filesystem>

#include "../Model/model.h"

Model *Model::instance_ = nullptr;
namespace fs = std::filesystem;

class MyTest : public ::testing::Test {
  // MyTest() {
  //   if (p.filename() == "3DViewer_v2.0") {
  //     p = fs::path("src/");
  //   }
  //   if (p.filename() == "src") {
  //     p = fs::path("src/");
  //   }
  //   if (p.filename() == "tests") {
  //     p = fs::path("tests/");
  //   }
  // }

 protected:
  Model *m = Model::getInstance();
  // fs::path p = fs::current_path();
  // std::string prefix = p.string();
};

TEST_F(MyTest, test) {
  m->setFilename("../../../src/Obj/cube.obj");
  fs::path p = fs::current_path();
  std::cout << "p.string() = " << p.string() << std::endl;

  EXPECT_NO_THROW(m->Parse());
  EXPECT_EQ(m->getPolygonsCount(), 10);
  EXPECT_EQ(m->getVerticesCount(), 8);

  S21Matrix matrix{8, 3, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1,
                   1, 1, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1};
  EXPECT_EQ(*(m->getData()->vertices), matrix);

  EXPECT_EQ(m->getPolygon(0), std::vector<size_t>({1, 7, 5}));
  EXPECT_EQ(m->getPolygon(1), std::vector<size_t>({0, 2, 6}));
  EXPECT_EQ(m->getPolygon(2), std::vector<size_t>({0, 3, 2}));
  EXPECT_EQ(m->getPolygon(3), std::vector<size_t>({0, 1, 3}));
  EXPECT_EQ(m->getPolygon(4), std::vector<size_t>({2, 7, 6}));
  EXPECT_EQ(m->getPolygon(5), std::vector<size_t>({2, 3, 7}));
  EXPECT_EQ(m->getPolygon(6), std::vector<size_t>({4, 6, 7}));
  EXPECT_EQ(m->getPolygon(7), std::vector<size_t>({4, 7, 5}));
  EXPECT_EQ(m->getPolygon(8), std::vector<size_t>({0, 4, 5}));
  EXPECT_EQ(m->getPolygon(9), std::vector<size_t>({0, 5, 1}));
}

TEST_F(MyTest, test2) {
  m->setFilename("../../../src/Obj/cube_negate.obj");
  EXPECT_NO_THROW(m->Parse());
  EXPECT_EQ(m->getPolygonsCount(), 6);
  EXPECT_EQ(m->getVerticesCount(), 8);

  S21Matrix matrix{8, 3,  -1, -1, 1, 1,  -1, 1, 1, 1,  1,  -1, 1,
                   1, -1, -1, -1, 1, -1, -1, 1, 1, -1, -1, 1,  -1};
  EXPECT_EQ(*(m->getData()->vertices), matrix);

  EXPECT_EQ(m->getPolygon(0), std::vector<size_t>({7, 6, 5, 4}));
  EXPECT_EQ(m->getPolygon(1), std::vector<size_t>({3, 0, 1, 2}));
  EXPECT_EQ(m->getPolygon(2), std::vector<size_t>({7, 3, 2, 6}));
  EXPECT_EQ(m->getPolygon(3), std::vector<size_t>({6, 2, 1, 5}));
  EXPECT_EQ(m->getPolygon(4), std::vector<size_t>({5, 1, 0, 4}));
  EXPECT_EQ(m->getPolygon(5), std::vector<size_t>({3, 7, 4, 0}));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}