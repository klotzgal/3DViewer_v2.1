#include "affine.h"

namespace s21 {

void Scale::exec(Parser::data &data, double value) {
  if (value == 0) {
    return;
  }
  for (size_t i = 0; i < data.vertices.size(); i++) {
    data.vertices[i] *= value;
  }
}

void MoveX::exec(Parser::data &data, double value) {
  for (size_t i = 0; i < data.vertices.size(); i += 3) {
    data.vertices[i] += value;
  }
}

void MoveY::exec(Parser::data &data, double value) {
  for (size_t i = 1; i < data.vertices.size(); i += 3) {
    data.vertices[i] += value;
  }
}

void MoveZ::exec(Parser::data &data, double value) {
  for (size_t i = 2; i < data.vertices.size(); i += 3) {
    data.vertices[i] += value;
  }
}

void RotateX::exec(Parser::data &data, double value) {
  value = value * M_PI / 180;
  for (size_t i = 0; i < data.vertices.size(); i += 3) {
    double Y = data.vertices[i + 1];
    double Z = data.vertices[i + 2];
    data.vertices[i + 1] = Y * cosl(value) + Z * sinl(value);
    data.vertices[i + 2] = -Y * sinl(value) + Z * cosl(value);
  }
  for (size_t i = 0; i < data.averaged_normals.size(); i += 3) {
    double Y = data.averaged_normals[i + 1];
    double Z = data.averaged_normals[i + 2];
    data.averaged_normals[i + 1] = Y * cosl(value) + Z * sinl(value);
    data.averaged_normals[i + 2] = -Y * sinl(value) + Z * cosl(value);
  }
}

void RotateY::exec(Parser::data &data, double value) {
  value = value * M_PI / 180;
  for (size_t i = 0; i < data.vertices.size(); i += 3) {
    double X = data.vertices[i];
    double Z = data.vertices[i + 2];
    data.vertices[i] = X * cosl(value) + Z * sinl(value);
    data.vertices[i + 2] = -X * sinl(value) + Z * cosl(value);
  }
  for (size_t i = 0; i < data.averaged_normals.size(); i += 3) {
    double X = data.averaged_normals[i];
    double Z = data.averaged_normals[i + 2];
    data.averaged_normals[i] = X * cosl(value) + Z * sinl(value);
    data.averaged_normals[i + 2] = -X * sinl(value) + Z * cosl(value);
  }
}

void RotateZ::exec(Parser::data &data, double value) {
  value = value * M_PI / 180;
  for (size_t i = 0; i < data.vertices.size(); i += 3) {
    double X = data.vertices[i];
    double Y = data.vertices[i + 1];
    data.vertices[i] = X * cosl(value) + Y * sinl(value);
    data.vertices[i + 1] = -X * sinl(value) + Y * cosl(value);
  }
  for (size_t i = 0; i < data.averaged_normals.size(); i += 3) {
    double X = data.averaged_normals[i];
    double Y = data.averaged_normals[i + 1];
    data.averaged_normals[i] = X * cosl(value) + Y * sinl(value);
    data.averaged_normals[i + 1] = -X * sinl(value) + Y * cosl(value);
  }
}

}  // namespace s21