#ifndef CPP4_3DVIEWER_V2_0_SRC_MODEL_PARSER_H
#define CPP4_3DVIEWER_V2_0_SRC_MODEL_PARSER_H

#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <locale>
#include <sstream>
#include <string>
#include <vector>

// #include "../Libs/omp.h"
// #include "../Libs/s21_matrix_oop.h"

class Parser {
 public:
  Parser();
  ~Parser();
  struct data {
    std::vector<double> vertices;
    std::vector<std::vector<uint>> polygons;
    double max;
    data() : vertices(0, 0), polygons(0, std::vector<uint>(0)), max(-1) {}
    bool isEmpty() { return vertices.size() / 3 == 0 || polygons.size() == 0; }

    void print() {
      std::cout << std::fixed;
      std::cout << "vertices_count = " << vertices.size() / 3 << std::endl;
      std::cout << "polygons_count = " << polygons.size() << std::endl;
      if (!isEmpty()) {
        std::cout << "vertices:" << std::endl;
        for (size_t i = 0; i < vertices.size(); i += 3) {
          std::cout << i / 3 << " " << std::setprecision(15) << vertices[i]
                    << " " << vertices[i + 1] << " " << vertices[i + 2]
                    << std::endl;
        }
        std::cout << "polygons.capacity() = " << polygons.capacity()
                  << std::endl;
        for (size_t i = 0; i < polygons.size(); i++) {
          std::cout << polygons[i].size() << " ";
          for (size_t j = 0; j < polygons[i].size(); j++) {
            std::cout << polygons[i][j] << " ";
          }
          std::cout << std::endl;
        }
      }
    }
  };

  void parse(const std::string filename, data *data);

 private:
  void parseVAndF(std::ifstream &file, data *data);
  void cleanData(data *data);
  void normalizeVertices(data *data);
};

#endif  // CPP4_3DVIEWER_V2_0_SRC_MODEL_PARSER_H