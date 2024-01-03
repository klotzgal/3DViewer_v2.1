#ifndef CPP4_3DVIEWER_V2_0_SRC_MODEL_MODEL_H
#define CPP4_3DVIEWER_V2_0_SRC_MODEL_MODEL_H

#include <iostream>

#include "../Libs/s21_matrix_oop.h"
#include "parser.h"

class Model {
  struct data;

 public:
  Model();
  ~Model();
  void setFilename(const std::string &filename) { filename_ = filename; }
  std::string getFilename() { return filename_; }

 private:
  struct data {
    struct Facets {
      int *vertexes = nullptr;
      int numbers_of_vertexes_in_facets = 0;
    };

    size_t vertices_count;
    size_t facets_count;
    S21Matrix vertices;
    Facets facets;

    data() : vertices_count(0), facets_count(0), vertices(), facets() {
      std::cout << "Data constructor" << std::endl;
    }
    ~data() {
      std::cout << "Data constructor" << std::endl;
      vertices_count = 0;
      facets_count = 0;
    }
  };

  data *data_;
  std::string filename_;
  Parser parser_;
};

#endif  // CPP4_3DVIEWER_V2_0_SRC_MODEL_MODEL_H