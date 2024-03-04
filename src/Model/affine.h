#ifndef CPP4_3DVIEWER_V2_0_SRC_MODEL_AFFINE_H
#define CPP4_3DVIEWER_V2_0_SRC_MODEL_AFFINE_H

#include "parser.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif  // M_PI

namespace s21 {
class IStrategy {
 public:
  virtual ~IStrategy() = default;
  virtual void exec(Parser::data &data, double value) = 0;
};

class Scale : public IStrategy {
 public:
  Scale() = default;
  void exec(Parser::data &data, double value) override;
};

class MoveX : public IStrategy {
 public:
  MoveX() = default;
  void exec(Parser::data &data, double value) override;
};

class MoveY : public IStrategy {
 public:
  MoveY() = default;
  void exec(Parser::data &data, double value) override;
};

class MoveZ : public IStrategy {
 public:
  MoveZ() = default;
  void exec(Parser::data &data, double value) override;
};

class RotateX : public IStrategy {
 public:
  RotateX() = default;
  void exec(Parser::data &data, double value) override;
};

class RotateY : public IStrategy {
 public:
  RotateY() = default;
  void exec(Parser::data &data, double value) override;
};

class RotateZ : public IStrategy {
 public:
  RotateZ() = default;
  void exec(Parser::data &data, double value) override;
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_SRC_MODEL_AFFINE_H