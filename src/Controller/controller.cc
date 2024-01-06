#include "controller.h"

void Controller::Scale(double k) {
  ScaleM s;
  model_->ChangeModel(&s, k);
}

void Controller::Move(char c, double k) {
  IStrategy *m = nullptr;
  if (c == 'x') {
    m = new MoveX();
  } else if (c == 'y') {
    m = new MoveY();
  } else if (c == 'z') {
    m = new MoveZ();
  }
  model_->ChangeModel(m, k);
  if (m) {
    delete m;
  }
}

void Controller::Rotate(char c, double k) {
  IStrategy *m = nullptr;
  if (c == 'x') {
    m = new RotateX();
  } else if (c == 'y') {
    m = new RotateY();
  } else if (c == 'z') {
    m = new RotateZ();
  }
  model_->ChangeModel(m, k);
  if (m) {
    delete m;
  }
}