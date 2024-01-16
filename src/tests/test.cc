#include <gtest/gtest.h>

#include "../Model/model.h"

Model *Model::instance_ = nullptr;

class MyTest : public ::testing::Test {
 protected:
  Model *m = Model::getInstance();
};

TEST_F(MyTest, test) {
  m->setFilename("../Obj/cube.obj");
  EXPECT_NO_THROW(m->Parse());
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}