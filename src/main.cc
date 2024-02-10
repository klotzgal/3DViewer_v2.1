#include <filesystem>

#include "Model/model.h"

namespace fs = std::filesystem;

Model* Model::instance_ = nullptr;

int main() {
  Model* model = Model::getInstance();
  model->setFilename(
      "/home/klotzgal/Desktop/kl/S21_CPP/3DViewer_v2.0/src/Obj/"
      "IphoneX.obj");
  // /Users/klotzgal/Desktop/kl/3DViewer_v2.0/src/Obj/cube.obj
  // /home/klotzgal/Desktop/kl/S21_CPP/3DViewer_v2.0/src/Obj/cube.obj
  std::cout << model->getFilename() << std::endl;
  std::string test = "1,2";
  std::cout << stod(test) << std::endl;
  try {
    model->parse();
    model->print();
  } catch (const std::exception& e) {
    std::cerr << e.what() << " Error" << '\n';
  }
  std::vector<double> normal = model->calcFloatNormal(0);
  return 0;
}