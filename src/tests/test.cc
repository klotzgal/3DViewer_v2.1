#include <gtest/gtest.h>

#include <filesystem>

#include "../Model/model.h"

Model *Model::instance_ = nullptr;
#ifdef __APPLE__
namespace fs = std::__fs::filesystem;
#else
namespace fs = std::filesystem;
#endif

class MyTest : public ::testing::Test {
 public:
  MyTest() {
    fs::path obj("src/Obj");
    fs::path cur_path = fs::current_path();
    auto cur = --(cur_path.end());
    for (; std::find(obj.begin(), obj.end(), *cur) == obj.end() &&
           *cur != "3DViewer_v2.0";
         --cur) {
      pref /= "..";
    }
    if (*cur == "3DViewer_v2.0") {
      pref /= obj;
    } else {
      for (auto it1 = std::find(obj.begin(), obj.end(), *cur); it1 != obj.end();
           it1++) {
        pref /= *it1;
      }
    }
  }

 protected:
  Model *m = Model::getInstance();
  fs::path pref;
  // std::string prefix = p.string();
};

TEST_F(MyTest, test) {
  m->setFilename(pref.string() + "/cube.obj");
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
  m->setFilename(pref.string() + "/cube_negate.obj");
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