#ifndef CPP4_3DVIEWER_V2_0_SRC_MODEL_PARSER_H
#define CPP4_3DVIEWER_V2_0_SRC_MODEL_PARSER_H

#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// #include "../Libs/omp.h"
#include "../Libs/s21_matrix_oop.h"

class Parser {
 public:
  Parser();
  ~Parser();
  struct data {
    struct Polygon {
      std::vector<size_t> vertexes;
      size_t numbers_of_vertexes_in_polygons = 0;
    };

    size_t vertices_count;
    size_t polygons_count;
    S21Matrix *vertices;
    std::vector<Polygon> *polygons;
    double max;
    data()
        : vertices_count(0),
          polygons_count(0),
          vertices(nullptr),
          polygons(nullptr),
          max(-1) {
      std::cout << "Data constructor" << std::endl;
    }
    ~data() {
      std::cout << "Data constructor" << std::endl;
      delete vertices;
      delete polygons;
      vertices_count = 0;
      polygons_count = 0;
    }

    bool isEmpty() { return vertices_count == 0 || polygons_count == 0; }

    void Print() {
      std::cout << std::fixed;
      std::cout << "vertices_count = " << vertices_count << std::endl;
      std::cout << "polygons_count = " << polygons_count << std::endl;
      if (!isEmpty()) {
        std::cout << "vertices:" << std::endl;
        for (size_t i = 0; i < vertices_count; i++) {
          std::cout << i + 1 << " " << std::setprecision(15)
                    << (*vertices)(i, 0) << " " << (*vertices)(i, 1) << " "
                    << (*vertices)(i, 2) << std::endl;
        }
        std::cout << "polygons = " << (*polygons).capacity() << std::endl;
        for (size_t i = 0; i < polygons_count; i++) {
          std::cout << (*polygons)[i].numbers_of_vertexes_in_polygons << " ";
          for (size_t j = 0; j < (*polygons)[i].numbers_of_vertexes_in_polygons;
               j++) {
            std::cout << (*polygons)[i].vertexes[j] << " ";
          }
          std::cout << std::endl;
        }
      }
    }
  };

  void Parse(const std::string filename, data *data);

 private:
  void CountVAndF(std::ifstream &file, data *data);
  void ParseVAndF(std::ifstream &file, data *data);
  void DataMemoryAllocation(data *data);
  void DataMemoryDeAllocation(data *data);
  void NormalizeVertices(data *data);
};

#endif  // CPP4_3DVIEWER_V2_0_SRC_MODEL_PARSER_H