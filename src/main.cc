#include <filesystem>

#include "Model/model.h"
#define STB_IMAGE_IMPLEMENTATION
#include "Libs/stb_image.h"

namespace fs = std::filesystem;

Model* Model::instance_ = nullptr;

int main() {
  Model* model = Model::getInstance();
  model->setFilename(
      "/home/klotzgal/Desktop/kl/S21_CPP/3DViewer_v2.0/src/Obj/"
      "IphoneX.obj");
  // /Users/klotzgal/Desktop/kl/3DViewer_v2.0/src/Obj/cube.obj
  // /home/klotzgal/Desktop/kl/S21_CPP/3DViewer_v2.0/src/Obj/cube.obj
  try {
    model->parse();
    model->parse();
    model->print();
  } catch (const std::exception& e) {
    std::cerr << e.what() << " Error" << '\n';
  }
  int width = 0, height = 0, cnt = 0;
  unsigned char* data2 = stbi_load("texture.bmp", &width, &height, &cnt, 0);
  std::cout << width << " " << height << " " << cnt << std::endl;
  stbi_image_free(data2);
  return 0;
}