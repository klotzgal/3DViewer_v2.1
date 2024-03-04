#ifndef CPP4_3DVIEWER_V2_0_SRC_MODEL_PARSER_H
#define CPP4_3DVIEWER_V2_0_SRC_MODEL_PARSER_H

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <locale>
#include <sstream>
#include <string>
#include <vector>

namespace s21 {
class Parser {
 public:
  Parser() {}
  ~Parser() {}
  struct data {
    std::vector<double> vertices;
    std::vector<double> normals;
    std::vector<std::vector<uint>> polygons;
    std::vector<std::vector<uint>> polygons_normals;
    std::vector<double> averaged_normals;
    double max;
    data()
        : vertices(0, 0),
          normals(0, 0),
          polygons(0, std::vector<uint>(0)),
          polygons_normals(0, std::vector<uint>(0)),
          averaged_normals(0, 0),
          max(-1) {}
    bool isEmpty() { return vertices.size() / 3 == 0 || polygons.size() == 0; }
    bool isHaveNormals() { return !normals.empty(); }

    void print() {
      std::cout << std::fixed;
      std::cout << "vertices_count = " << vertices.size() / 3 << std::endl;
      std::cout << "polygons_count = " << polygons.size() << std::endl;
      std::cout << "polygons_normals_count = " << polygons_normals.size()
                << std::endl;
      std::cout << "normals_count = " << normals.size() / 3 << std::endl;
      // if (!isEmpty()) {
      //   std::cout << "vertices:" << std::endl;
      //   for (size_t i = 0; i < vertices.size(); i += 3) {
      //     std::cout << i / 3 << " " << std::setprecision(15) << vertices[i]
      //               << " " << vertices[i + 1] << " " << vertices[i + 2]
      //               << std::endl;
      //   }
      //   std::cout << "polygons.capacity() = " << polygons.capacity()
      //             << std::endl;
      //   for (size_t i = 0; i < polygons.size(); i++) {
      //     std::cout << polygons[i].size() << " ";
      //     for (size_t j = 0; j < polygons[i].size(); j++) {
      //       std::cout << polygons[i][j];
      //       if (isHaveNormals()) {
      //         std::cout << "/" << polygons_normals[i][j];
      //       }
      //       std::cout << " ";
      //     }
      //     std::cout << std::endl;
      //   }
      //   std::cout << "normals:" << std::endl;
      //   for (size_t i = 0; i < normals.size(); i += 3) {
      //     std::cout << i / 3 << " " << std::setprecision(15) << normals[i]
      //               << " " << normals[i + 1] << " " << normals[i + 2]
      //               << std::endl;
      //   }
      // }
    }
  };

  void parse(const std::string filename, data *data);

 private:
  void parseVAndF(std::ifstream &file, data *data);
  void cleanData(data *data);
  void normalizeVertices(data *data);
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_SRC_MODEL_PARSER_H