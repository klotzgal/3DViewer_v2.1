#include "controller.h"

namespace s21 {

void Controller::scale(double k) {
  Scale s;
  model_->changeModel(&s, k);
}

void Controller::move(double x, double y, double z) {
  IStrategy *m = nullptr;
  if (x) {
    m = new MoveX();
    model_->changeModel(m, x);
    delete m;
  }
  if (y) {
    m = new MoveY();
    model_->changeModel(m, y);
    delete m;
  }
  if (z) {
    m = new MoveZ();
    model_->changeModel(m, z);
    delete m;
  }
}

void Controller::rotate(double x, double y, double z) {
  IStrategy *m = nullptr;
  if (x) {
    m = new RotateX();
    model_->changeModel(m, x);
    delete m;
  }
  if (y) {
    m = new RotateY();
    model_->changeModel(m, y);
    delete m;
  }
  if (z) {
    m = new RotateZ();
    model_->changeModel(m, z);
    delete m;
  }
}

}  // namespace s21