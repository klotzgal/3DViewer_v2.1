#include <gtest/gtest.h>

#include <filesystem>

#include "../Model/affine.h"
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
    std::cout << "cur_path = " << cur_path << std::endl;
    while (std::find(obj.begin(), obj.end(), *cur) == obj.end() &&
           *cur != "3DViewer_v2.0") {
      --cur;
      pref /= "..";
    }
    std::cout << "cur = " << *cur << std::endl;
    if (*cur == "3DViewer_v2.0") {
      pref /= obj;
    } else {
      for (auto it1 = (++std::find(obj.begin(), obj.end(), *cur));
           it1 != obj.end(); it1++) {
        pref /= *it1;
      }
    }
    std::cout << "pref = " << pref << std::endl;
  }

 protected:
  Model *m = Model::getInstance();
  fs::path pref;
  // std::string prefix = p.string();
};

TEST_F(MyTest, test) {
  m->setFilename(pref.string() + "/cube.obj");
  EXPECT_NO_THROW(m->parse());
  // Vertices
  std::vector<double> vertices{0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0,
                               0.0, 0.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0,
                               0.0, 1.0, 1.0, 1.0, 0.0, 1.0, 1.0, 1.0};
  auto m_vertices = m->getVertices();
  EXPECT_EQ(m_vertices.size(), vertices.size());
  for (size_t i = 0; i < vertices.size(); i++) {
    EXPECT_EQ(m_vertices[i], vertices[i]);
  }
  // Polygons
  std::vector<std::vector<uint>> polygons{
      {1, 7, 5}, {0, 2, 6}, {0, 3, 2}, {0, 1, 3}, {2, 7, 6},
      {2, 3, 7}, {4, 6, 7}, {4, 7, 5}, {0, 4, 5}, {0, 5, 1}};
  EXPECT_EQ(m->getPolygonsCount(), polygons.size());
  for (size_t i = 0; i < polygons.size(); i++) {
    EXPECT_EQ(m->getPolygon(i), polygons[i]);
  }
}

TEST_F(MyTest, test2) {
  m->setFilename(pref.string() + "/cube_negate.obj");
  EXPECT_NO_THROW(m->parse());
  // Vertices
  std::vector<double> vertices{-1, -1, 1,  1, -1, 1,  1, 1, 1,  -1, 1, 1,
                               -1, -1, -1, 1, -1, -1, 1, 1, -1, -1, 1, -1};
  auto m_vertices = m->getVertices();
  EXPECT_EQ(m_vertices.size(), vertices.size());
  for (size_t i = 0; i < vertices.size(); i++) {
    EXPECT_EQ(m_vertices[i], vertices[i]);
  }
  // Polygons
  std::vector<std::vector<uint>> polygons{{7, 6, 5, 4}, {3, 0, 1, 2},
                                          {7, 3, 2, 6}, {6, 2, 1, 5},
                                          {5, 1, 0, 4}, {3, 7, 4, 0}};
  EXPECT_EQ(m->getPolygonsCount(), polygons.size());
  for (size_t i = 0; i < polygons.size(); i++) {
    EXPECT_EQ(m->getPolygon(i), polygons[i]);
  }
  // Normals
  std::vector<double> normals{-2, -2, 2,  2, -2, 2,  2, 2, 2,  -2, 2, 2,
                              -2, -2, -2, 2, -2, -2, 2, 2, -2, -2, 2, -2};
  auto m_normals = m->getNormals();
  EXPECT_EQ(m_normals.size(), normals.size());
  for (size_t i = 0; i < normals.size(); i++) {
    EXPECT_EQ(m_normals[i], normals[i]);
  }
  // Polygons Normals
  std::vector<std::vector<uint>> polygons_normals{{8, 7, 6, 5}, {4, 1, 2, 3},
                                                  {8, 4, 3, 7}, {7, 3, 2, 6},
                                                  {6, 2, 1, 5}, {4, 8, 5, 1}};
  EXPECT_EQ(m->getPolygonsNormalsCount(), polygons_normals.size());
  for (size_t i = 0; i < polygons_normals.size(); i++) {
    EXPECT_EQ(m->getPolygonNormals(i), polygons_normals[i]);
  }
}

TEST_F(MyTest, move_x_test) {
  m->setFilename(pref.string() + "/cube_negate.obj");
  EXPECT_NO_THROW(m->parse());
  IStrategy *strategy = new MoveX();
  m->changeModel(strategy, 1);
  delete strategy;
  // Vertices
  std::vector<double> vertices{0, -1, 1,  2, -1, 1,  2, 1, 1,  0,  1, 1,
                               0, -1, -1, 2, -1, -1, 2, 1, -1, -0, 1, -1};
  auto m_vertices = m->getVertices();
  EXPECT_EQ(m_vertices.size(), vertices.size());
  for (size_t i = 0; i < vertices.size(); i++) {
    EXPECT_EQ(m_vertices[i], vertices[i]);
  }
  // Normals
  std::vector<double> normals{-1, -2, 2,  3, -2, 2,  3, 2, 2,  -1, 2, 2,
                              -1, -2, -2, 3, -2, -2, 3, 2, -2, -1, 2, -2};
  auto m_normals = m->getNormals();
  EXPECT_EQ(m_normals.size(), normals.size());
  for (size_t i = 0; i < normals.size(); i++) {
    EXPECT_EQ(m_normals[i], normals[i]);
  }
}

TEST_F(MyTest, move_y_test) {
  m->setFilename(pref.string() + "/cube_negate.obj");
  EXPECT_NO_THROW(m->parse());
  IStrategy *strategy = new MoveY();
  m->changeModel(strategy, 1);
  delete strategy;
  // Vertices
  std::vector<double> vertices{-1, 0, 1,  1, 0, 1,  1, 2, 1,  -1, 2, 1,
                               -1, 0, -1, 1, 0, -1, 1, 2, -1, -1, 2, -1};
  auto m_vertices = m->getVertices();
  EXPECT_EQ(m_vertices.size(), vertices.size());
  for (size_t i = 0; i < vertices.size(); i++) {
    EXPECT_EQ(m_vertices[i], vertices[i]);
  }
  // Normals
  std::vector<double> normals{-2, -1, 2,  2, -1, 2,  2, 3, 2,  -2, 3, 2,
                              -2, -1, -2, 2, -1, -2, 2, 3, -2, -2, 3, -2};
  auto m_normals = m->getNormals();
  EXPECT_EQ(m_normals.size(), normals.size());
  for (size_t i = 0; i < normals.size(); i++) {
    EXPECT_EQ(m_normals[i], normals[i]);
  }
}

TEST_F(MyTest, move_z_test) {
  m->setFilename(pref.string() + "/cube_negate.obj");
  EXPECT_NO_THROW(m->parse());
  IStrategy *strategy = new MoveZ();
  m->changeModel(strategy, 1);
  delete strategy;
  // Vertices
  std::vector<double> vertices{-1, -1, 2, 1, -1, 2, 1, 1, 2, -1, 1, 2,
                               -1, -1, 0, 1, -1, 0, 1, 1, 0, -1, 1, 0};
  auto m_vertices = m->getVertices();
  EXPECT_EQ(m_vertices.size(), vertices.size());
  for (size_t i = 0; i < vertices.size(); i++) {
    EXPECT_EQ(m_vertices[i], vertices[i]);
  }
  // Normals
  std::vector<double> normals{-2, -2, 3,  2, -2, 3,  2, 2, 3,  -2, 2, 3,
                              -2, -2, -1, 2, -2, -1, 2, 2, -1, -2, 2, -1};
  auto m_normals = m->getNormals();
  EXPECT_EQ(m_normals.size(), normals.size());
  for (size_t i = 0; i < normals.size(); i++) {
    EXPECT_EQ(m_normals[i], normals[i]);
  }
}

TEST_F(MyTest, scale_test) {
  m->setFilename(pref.string() + "/cube_negate.obj");
  EXPECT_NO_THROW(m->parse());
  IStrategy *strategy = new Scale();
  m->changeModel(strategy, 2);
  delete strategy;
  // Vertices
  std::vector<double> vertices{-2, -2, 2,  2, -2, 2,  2, 2, 2,  -2, 2, 2,
                               -2, -2, -2, 2, -2, -2, 2, 2, -2, -2, 2, -2};

  auto m_vertices = m->getVertices();
  EXPECT_EQ(m_vertices.size(), vertices.size());
  for (size_t i = 0; i < vertices.size(); i++) {
    EXPECT_EQ(m_vertices[i], vertices[i]);
  }
  // Normals
  std::vector<double> normals{-4, -4, 4,  4, -4, 4,  4, 4, 4,  -4, 4, 4,
                              -4, -4, -4, 4, -4, -4, 4, 4, -4, -4, 4, -4};
  auto m_normals = m->getNormals();
  EXPECT_EQ(m_normals.size(), normals.size());
  for (size_t i = 0; i < normals.size(); i++) {
    EXPECT_EQ(m_normals[i], normals[i]);
  }
}

TEST_F(MyTest, rotate_x_test) {
  m->setFilename(pref.string() + "/cube_negate.obj");
  EXPECT_NO_THROW(m->parse());
  IStrategy *strategy = new RotateX();
  m->changeModel(strategy, 180);
  delete strategy;
  // Vertices
  std::vector<double> vertices{-1, 1, -1, 1, 1, -1, 1, -1, -1, -1, -1, -1,
                               -1, 1, 1,  1, 1, 1,  1, -1, 1,  -1, -1, 1};
  auto m_vertices = m->getVertices();
  EXPECT_EQ(m_vertices.size(), vertices.size());
  for (size_t i = 0; i < vertices.size(); i++) {
    EXPECT_DOUBLE_EQ(m_vertices[i], vertices[i]);
  }
  // Normals
  std::vector<double> normals{-2, 2, -2, 2, 2, -2, 2, -2, -2, -2, -2, -2,
                              -2, 2, 2,  2, 2, 2,  2, -2, 2,  -2, -2, 2};
  auto m_normals = m->getNormals();
  EXPECT_EQ(m_normals.size(), normals.size());
  for (size_t i = 0; i < normals.size(); i++) {
    EXPECT_DOUBLE_EQ(m_normals[i], normals[i]);
  }
}

TEST_F(MyTest, rotate_y_test) {
  m->setFilename(pref.string() + "/cube_negate.obj");
  EXPECT_NO_THROW(m->parse());
  IStrategy *strategy = new RotateY();
  m->changeModel(strategy, 180);
  delete strategy;
  // Vertices
  std::vector<double> vertices{1, -1, -1, -1, -1, -1, -1, 1, -1, 1, 1, -1,
                               1, -1, 1,  -1, -1, 1,  -1, 1, 1,  1, 1, 1};
  auto m_vertices = m->getVertices();
  EXPECT_EQ(m_vertices.size(), vertices.size());
  for (size_t i = 0; i < vertices.size(); i++) {
    EXPECT_DOUBLE_EQ(m_vertices[i], vertices[i]);
  }
  // Normals
  std::vector<double> normals{2, -2, -2, -2, -2, -2, -2, 2, -2, 2, 2, -2,
                              2, -2, 2,  -2, -2, 2,  -2, 2, 2,  2, 2, 2};
  auto m_normals = m->getNormals();
  EXPECT_EQ(m_normals.size(), normals.size());
  for (size_t i = 0; i < normals.size(); i++) {
    EXPECT_DOUBLE_EQ(m_normals[i], normals[i]);
  }
}

TEST_F(MyTest, rotate_z_test) {
  m->setFilename(pref.string() + "/cube_negate.obj");
  EXPECT_NO_THROW(m->parse());
  IStrategy *strategy = new RotateZ();
  m->changeModel(strategy, 180);
  delete strategy;
  // Vertices
  std::vector<double> vertices{1, 1, 1,  -1, 1, 1,  -1, -1, 1,  1, -1, 1,
                               1, 1, -1, -1, 1, -1, -1, -1, -1, 1, -1, -1};
  auto m_vertices = m->getVertices();
  EXPECT_EQ(m_vertices.size(), vertices.size());
  for (size_t i = 0; i < vertices.size(); i++) {
    EXPECT_DOUBLE_EQ(m_vertices[i], vertices[i]);
  }
  // Normals
  std::vector<double> normals{2, 2, 2,  -2, 2, 2,  -2, -2, 2,  2, -2, 2,
                              2, 2, -2, -2, 2, -2, -2, -2, -2, 2, -2, -2};
  auto m_normals = m->getNormals();
  EXPECT_EQ(m_normals.size(), normals.size());
  for (size_t i = 0; i < normals.size(); i++) {
    EXPECT_DOUBLE_EQ(m_normals[i], normals[i]);
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}