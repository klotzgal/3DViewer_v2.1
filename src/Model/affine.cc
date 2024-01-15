#include "affine.h"

void ScaleM::exec(Parser::data &data, double value) {
  if (value == 0) {
    return;
  }
  for (size_t i = 0; i < data.vertices_count; i++) {
    (*data.vertices)(i, 0) *= value;
    (*data.vertices)(i, 1) *= value;
    (*data.vertices)(i, 2) *= value;
  }
}

void MoveX::exec(Parser::data &data, double value) {
  for (size_t i = 0; i < data.vertices_count; i++) {
    (*data.vertices)(i, 0) += value;
  }
}

void MoveY::exec(Parser::data &data, double value) {
  for (size_t i = 0; i < data.vertices_count; i++) {
    (*data.vertices)(i, 1) += value;
  }
}

void MoveZ::exec(Parser::data &data, double value) {
  for (size_t i = 0; i < data.vertices_count; i++) {
    (*data.vertices)(i, 2) += value;
  }
}

void RotateX::exec(Parser::data &data, double value) {
  value = value * M_PI / 180;
  for (size_t i = 0; i < data.vertices_count; i++) {
    double Y = (*data.vertices)(i, 1);
    double Z = (*data.vertices)(i, 2);
    (*data.vertices)(i, 1) = Y * cosl(value) - Z * sinl(value);
    (*data.vertices)(i, 2) = Y * sinl(value) + Z * cosl(value);
  }
}

void RotateY::exec(Parser::data &data, double value) {
  value = value * M_PI / 180;
  for (size_t i = 0; i < data.vertices_count; i++) {
    double X = (*data.vertices)(i, 0);
    double Z = (*data.vertices)(i, 2);
    (*data.vertices)(i, 0) = X * cosl(value) + Z * sinl(value);
    (*data.vertices)(i, 2) = -X * sinl(value) + Z * cosl(value);
  }
}

void RotateZ::exec(Parser::data &data, double value) {
  value = value * M_PI / 180;
  for (size_t i = 0; i < data.vertices_count; i++) {
    double X = (*data.vertices)(i, 0);
    double Y = (*data.vertices)(i, 1);
    (*data.vertices)(i, 0) = X * cosl(value) - Y * sinl(value);
    (*data.vertices)(i, 1) = X * sinl(value) + Y * cosl(value);
  }
}
