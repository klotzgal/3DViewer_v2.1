#include "Controller/controller.h"

Model* Model::instance_ = nullptr;

int main() {
  Model* model = Model::getInstance();
  model->setFilename(
      "/home/klotzgal/Desktop/kl/S21_CPP/3DViewer_v2.0/src/Obj/skull.obj");
  // /Users/klotzgal/Desktop/kl/3DViewer_v2.0/src/Obj/cube.obj
  // /home/klotzgal/Desktop/kl/S21_CPP/3DViewer_v2.0/src/Obj/cube.obj
  std::cout << model->getFilename() << std::endl;
  std::string test = "1,2";
  std::cout << stod(test) << std::endl;
  try {
    model->Parse();
    model->Parse();
    //
    // model->ChangeModel(&rx, 90);
  } catch (const std::exception& e) {
    std::cerr << e.what() << " Error" << '\n';
  }
  Controller c(model);
  auto x = c.getPolygon(0).vertexes.data();
  for (size_t i = 0; i < c.getPolygon(0).numbers_of_vertexes_in_polygons; ++i) {
    std::cout << (x + i) << " ";
  }
  // c.Print();
  return 0;
}