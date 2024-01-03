#ifndef CPP4_3DVIEWER_V2_0_SRC_MODEL_PARSER_H
#define CPP4_3DVIEWER_V2_0_SRC_MODEL_PARSER_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "../Libs/omp.h"
#include "../Libs/s21_matrix_oop.h"

class Parser {
 public:
  Parser();
  ~Parser();
  struct data {
    struct Facets {
      std::vector<int> vertexes;
      int numbers_of_vertexes_in_facets = 0;
    };

    size_t vertices_count;
    size_t facets_count;
    S21Matrix vertices;
    std::vector<Facets> facets;

    data() : vertices_count(0), facets_count(0), vertices(), facets() {
      std::cout << "Data constructor" << std::endl;
    }
    ~data() {
      std::cout << "Data constructor" << std::endl;
      vertices_count = 0;
      facets_count = 0;
    }
    void Print() {
      std::cout << "vertices_count = " << vertices_count << std::endl;
      std::cout << "facets_count = " << facets_count << std::endl;
      std::cout << "vertices:" << std::endl;
      for (size_t i = 0; i < vertices_count; i++) {
        std::cout << i + 1 << " " << vertices(i, 0) << " " << vertices(i, 1)
                  << " " << vertices(i, 2) << std::endl;
      }
      std::cout << "facets = " << facets.capacity() << std::endl;
      for (size_t i = 0; i < facets_count; i++) {
        std::cout << facets[i].numbers_of_vertexes_in_facets << " ";
        for (int j = 0; j < facets[i].numbers_of_vertexes_in_facets; j++) {
          std::cout << facets[i].vertexes[j] << " ";
        }
        std::cout << std::endl;
      }
    }
  };

  void Parse(const std::string filename, data *data);

 private:
  void CountVAndF(std::ifstream &file, data *data);
  void DataMemoryAllocation(data *data);
  void ParseVAndF(std::ifstream &file, data *data);
};

#endif  // CPP4_3DVIEWER_V2_0_SRC_MODEL_PARSER_H