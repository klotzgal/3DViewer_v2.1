#include "Controller/controller.h"

Model* Model::instance_ = nullptr;

int main() {
  Model* model = Model::getInstance();
  model->setFilename(
      "/Users/klotzgal/Desktop/kl/3DViewer_v2.0/src/Obj/cube.obj");
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
  auto x = c.getPolygon(0).data();
  for (size_t i = 0; i < c.getPolygon(0).size(); ++i) {
    std::cout << i << " " << (x + i) << std::endl;
  }
  // c.Print();
  return 0;
}