#include "model.h"

namespace s21 {

Model::Model() : filename_(""), data_(new data) {}

Model::~Model() { delete data_; }

void Model::parse() {
  parser_.parse(filename_, data_);
  // data_->Print();
  calcAveragedNormals();
}

std::vector<double> Model::calcFloatNormal(int i) {
  std::vector<double> v1 = {data_->vertices[data_->polygons[i][1] * 3] -
                                data_->vertices[data_->polygons[i][0] * 3],
                            data_->vertices[data_->polygons[i][1] * 3 + 1] -
                                data_->vertices[data_->polygons[i][0] * 3 + 1],
                            data_->vertices[data_->polygons[i][1] * 3 + 2] -
                                data_->vertices[data_->polygons[i][0] * 3 + 2]};
  std::vector<double> v2 = {data_->vertices[data_->polygons[i][2] * 3] -
                                data_->vertices[data_->polygons[i][0] * 3],
                            data_->vertices[data_->polygons[i][2] * 3 + 1] -
                                data_->vertices[data_->polygons[i][0] * 3 + 1],
                            data_->vertices[data_->polygons[i][2] * 3 + 2] -
                                data_->vertices[data_->polygons[i][0] * 3 + 2]};
  std::vector<double> normal = {v1[1] * v2[2] - v1[2] * v2[1],
                                v1[2] * v2[0] - v1[0] * v2[2],
                                v1[0] * v2[1] - v1[1] * v2[0]};
  double length = sqrt(normal[0] * normal[0] + normal[1] * normal[1] +
                       normal[2] * normal[2]);
  normal[0] /= length;
  normal[1] /= length;
  normal[2] /= length;
  return normal;
}

void Model::calcAveragedNormals() {
  data_->averaged_normals.clear();
  data_->averaged_normals.resize(data_->vertices.size());
  for (size_t i = 0; i < data_->polygons.size(); ++i) {
    std::vector<double> normal = calcFloatNormal(i);
    for (size_t j = 0; j < data_->polygons[i].size(); ++j) {
      data_->averaged_normals[data_->polygons[i][j] * 3] += normal[0] / 2;
      data_->averaged_normals[data_->polygons[i][j] * 3 + 1] += normal[1] / 2;
      data_->averaged_normals[data_->polygons[i][j] * 3 + 2] += normal[2] / 2;
    }
  }
}

}  // namespace s21
