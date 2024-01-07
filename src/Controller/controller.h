#ifndef CPP4_3DVIEWER_V2_0_SRC_MODEL_CONTROLLER_H
#define CPP4_3DVIEWER_V2_0_SRC_MODEL_CONTROLLER_H

#include "../Model/model.h"
// #include "../Model/affine.h"

class Controller {
 public:
  explicit Controller(Model* model) : model_(model) {}
  ~Controller() {}

  void Parse() { model_->Parse(); }
  void Scale(double k);
  void Move(char c, double k);
  void Rotate(char c, double k);

  // Getters and Setters
  void setFilename(const std::string& filename) {
    model_->setFilename(filename);
  }
  std::string getFilename() const { return model_->getFilename(); }
  size_t getVerticesCount() const { return model_->getVerticesCount(); }
  size_t getFacetsCount() const { return model_->getFacetsCount(); }
  double getX(int i) const { return model_->getX(i); }
  double getY(int i) const { return model_->getY(i); }
  double getZ(int i) const { return model_->getZ(i); }
  Parser::data::Facets& getFacet(int i) const { return model_->getFacet(i); }

 private:
  Model* model_;
};

#endif  // CPP4_3DVIEWER_V2_0_SRC_MODEL_CONTROLLER_H
