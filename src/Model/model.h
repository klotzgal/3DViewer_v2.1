#ifndef CPP4_3DVIEWER_V2_0_SRC_MODEL_MODEL_H
#define CPP4_3DVIEWER_V2_0_SRC_MODEL_MODEL_H

#include <iostream>

#include "affine.h"
#include "parser.h"

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
  void Parse();
  void Print() { data_->Print(); }
  bool isEmpty() { return data_->isEmpty(); }

  // Strategy
  void ChangeModel(IStrategy *strategy, double value) {
    if (strategy) strategy->exec(*data_, value);
  }

  // Getters
  data *getData() const noexcept { return data_; }

  size_t getVerticesCount() const noexcept { return data_->vertices_count; }
  size_t getPolygonsCount() const noexcept { return data_->polygons_count; }
  double getX(int i) const noexcept { return (*data_->vertices)(i, 0); }
  double getY(int i) const noexcept { return (*data_->vertices)(i, 1); }
  double getZ(int i) const noexcept { return (*data_->vertices)(i, 2); }
  Parser::data::Polygon &getPolygon(int i) const noexcept {
    return (*data_->polygons)[i];
  }

 private:
  std::string filename_;
  Parser parser_;
  data *data_;
  static Model *instance_;

  Model();
  Model(const Model &) = delete;
  Model &operator=(const Model &) = delete;
};

#endif  // CPP4_3DVIEWER_V2_0_SRC_MODEL_MODEL_H
