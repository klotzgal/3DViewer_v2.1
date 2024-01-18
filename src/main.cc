#include <filesystem>

#include "Model/model.h"

namespace fs = std::filesystem;

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
  fs::path pref;
  fs::path obj("3DViewer_v2.0/src/Obj");
  fs::path cur_path = fs::current_path();
  auto dir = cur_path.end();
  --dir;
  while (std::find(obj.begin(), obj.end(), *dir) == obj.end()) {
    --dir;
    pref /= "..";
  }

  auto it1 = std::find(obj.begin(), obj.end(), *dir);
  for (; it1 != obj.end(); it1++) {
    pref /= *it1;
  }

  std::cout << pref.string() << std::endl;

  return 0;
}