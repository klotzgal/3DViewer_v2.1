#include "controller.h"

void Controller::Scale(double k) {
  ScaleM s;
  model_->ChangeModel(&s, k);
}

void Controller::Move(double x, double y, double z) {
  IStrategy *m = nullptr;
  if (x) {
    m = new MoveX();
    model_->ChangeModel(m, x);
    delete m;
  }
  if (y) {
    m = new MoveY();
    model_->ChangeModel(m, y);
    delete m;
  }
  if (z) {
    m = new MoveZ();
    model_->ChangeModel(m, z);
    delete m;
  }
}

void Controller::Rotate(double x, double y, double z) {
  IStrategy *m = nullptr;
  if (x) {
    m = new RotateX();
    model_->ChangeModel(m, x);
    delete m;
  }
  if (y) {
    m = new RotateY();
    model_->ChangeModel(m, y);
    delete m;
  }
  if (z) {
    m = new RotateZ();
    model_->ChangeModel(m, z);
    delete m;
  }
}