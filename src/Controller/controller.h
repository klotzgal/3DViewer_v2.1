#ifndef CPP4_3DVIEWER_V2_0_SRC_MODEL_CONTROLLER_H
#define CPP4_3DVIEWER_V2_0_SRC_MODEL_CONTROLLER_H

#include <QFileDialog>

#include "../Model/model.h"
// #include "../Model/affine.h"

class Controller {
 public:
  explicit Controller(Model* model) : model_(model) {}
  ~Controller() {}
  void print() { model_->print(); }
  bool isEmpty() { return model_->isEmpty(); }

  void parse() { model_->parse(); }
  void scale(double k);
  void move(double x, double y, double z);
  void rotate(double x, double y, double z);

  // Getters and Setters
  void setFilename(const QString& filename) {
    model_->setFilename(filename.toStdString());
  }
  std::string getFilename() const { return model_->getFilename(); }
  Model::data* getData() const { return model_->getData(); }
  size_t getPolygonsCount() const { return model_->getPolygonsCount(); }
  double getX(int i) const { return model_->getX(i); }
  double getY(int i) const { return model_->getY(i); }
  double getZ(int i) const { return model_->getZ(i); }
  std::vector<double>& getVertices() { return model_->getVertices(); }
  std::vector<double>& getTextures() { return model_->getTextures(); }
  std::vector<uint>& getPolygon(int i) const { return model_->getPolygon(i); }
  std::vector<uint>& getPolygonTextures(int i) const {
    return model_->getPolygonTextures(i);
  }
  std::vector<double> calcFloatNormal(int i) {
    return model_->calcFloatNormal(i);
  }
  std::vector<double>& getAveragedNormals() {
    return model_->getAveragedNormals();
  }

 private:
  Model* model_;
};

#endif  // CPP4_3DVIEWER_V2_0_SRC_MODEL_CONTROLLER_H
