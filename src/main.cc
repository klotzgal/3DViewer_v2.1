#include "Model/model.h"

Model* Model::instance_ = nullptr;

int main() {
  setlocale(LC_ALL, "ru_RU.UTF-8");
  Model* model = Model::getInstance();
  model->setFilename(
      "/home/klotzgal/Desktop/kl/S21_CPP/3DViewer_v2.0/src/Obj/cube.obj");
  std::cout << model->getFilename() << std::endl;
  std::string test = "1,2";
  std::cout << stod(test) << std::endl;
  try {
    model->Parse();
    model->Parse();
    // RotateX rx;
    // model->ChangeModel(&rx, 90);
  } catch (const std::exception& e) {
    std::cerr << e.what() << " Error" << '\n';
  }

  return 0;
}