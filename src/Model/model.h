#ifndef CPP4_3DVIEWER_V2_0_SRC_MODEL_MODEL_H
#define CPP4_3DVIEWER_V2_0_SRC_MODEL_MODEL_H

#include <iostream>

#include "affine.h"
#include "parser.h"

namespace s21 {
class Model {
 public:
  using data = Parser::data;
  static Model *getInstance() {
    if (!instance_) {
      instance_ = new Model();
    }
    return instance_;
  }

  ~Model();
  void setFilename(const std::string &filename) { filename_ = filename; }
  std::string getFilename() const noexcept { return filename_; }
  void parse();
  void print() { data_->print(); }
  bool isEmpty() { return data_->isEmpty(); }
  bool isHaveNormals() { return data_->isHaveNormals(); }

  // Strategy
  void changeModel(IStrategy *strategy, double value) {
    if (strategy) strategy->exec(*data_, value);
  }

  // Getters
  data *getData() const noexcept { return data_; }

  size_t getPolygonsCount() const noexcept { return data_->polygons.size(); }
  size_t getPolygonsNormalsCount() const noexcept {
    return data_->polygons_normals.size();
  }
  double getX(int i) const noexcept { return data_->vertices[i * 3]; }
  double getY(int i) const noexcept { return data_->vertices[i * 3 + 1]; }
  double getZ(int i) const noexcept { return data_->vertices[i * 3 + 2]; }
  std::vector<double> &getVertices() noexcept { return data_->vertices; }
  std::vector<uint> &getPolygon(int i) noexcept { return data_->polygons[i]; }
  std::vector<double> &getNormals() noexcept { return data_->normals; }
  std::vector<uint> &getPolygonNormals(int i) noexcept {
    return data_->polygons_normals[i];
  }
  std::vector<double> calcFloatNormal(int i);
  void calcAveragedNormals();
  std::vector<double> &getAveragedNormals() { return data_->averaged_normals; }

 private:
  std::string filename_;
  Parser parser_;
  data *data_;
  static Model *instance_;

  Model();
  Model(const Model &) = delete;
  Model &operator=(const Model &) = delete;
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_SRC_MODEL_MODEL_H
