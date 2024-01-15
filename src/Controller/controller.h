#ifndef CPP4_3DVIEWER_V2_0_SRC_MODEL_CONTROLLER_H
#define CPP4_3DVIEWER_V2_0_SRC_MODEL_CONTROLLER_H

#include <QFileDialog>

#include "../Model/model.h"
// #include "../Model/affine.h"

class Controller {
 public:
  explicit Controller(Model* model) : model_(model) {}
  ~Controller() {}
  void Print() { model_->Print(); }
  bool isEmpty() { return model_->isEmpty(); }

  void Parse() { model_->Parse(); }
  void Scale(double k);
  void Move(double x, double y, double z);
  void Rotate(double x, double y, double z);

  // Getters and Setters
  void setFilename(const QString& filename) {
    model_->setFilename(filename.toStdString());
  }
  std::string getFilename() const { return model_->getFilename(); }
  size_t getVerticesCount() const { return model_->getVerticesCount(); }
  size_t getPolygonsCount() const { return model_->getPolygonsCount(); }
  double getX(int i) const { return model_->getX(i); }
  double getY(int i) const { return model_->getY(i); }
  double getZ(int i) const { return model_->getZ(i); }
  std::vector<size_t>& getPolygon(int i) const { return model_->getPolygon(i); }

 private:
  Model* model_;
};

#endif  // CPP4_3DVIEWER_V2_0_SRC_MODEL_CONTROLLER_H
