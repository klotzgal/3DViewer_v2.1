#ifndef CPP4_3DVIEWER_V2_0_SRC_MODEL_AFFINE_H
#define CPP4_3DVIEWER_V2_0_SRC_MODEL_AFFINE_H

#include "parser.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif  // M_PI

class IStrategy {
 public:
  virtual ~IStrategy() = default;
  virtual void exec(Parser::data &data, double value) = 0;
};

class ScaleM : public IStrategy {
 public:
  void exec(Parser::data &data, double value) override;
};

class MoveX : public IStrategy {
 public:
  void exec(Parser::data &data, double value) override;
};

class MoveY : public IStrategy {
 public:
  void exec(Parser::data &data, double value) override;
};

class MoveZ : public IStrategy {
 public:
  void exec(Parser::data &data, double value) override;
};

class RotateX : public IStrategy {
 public:
  void exec(Parser::data &data, double value) override;
};

class RotateY : public IStrategy {
 public:
  void exec(Parser::data &data, double value) override;
};

class RotateZ : public IStrategy {
 public:
  void exec(Parser::data &data, double value) override;
};

#endif  // CPP4_3DVIEWER_V2_0_SRC_MODEL_AFFINE_H