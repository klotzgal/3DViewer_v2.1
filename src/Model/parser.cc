#include "parser.h"

namespace s21 {

void Parser::parse(const std::string filename, data *data) {
  setlocale(LC_NUMERIC, "C");
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cout << "File \"" << filename << "\" not found" << std::endl;
    return;
  }
  if (!data->vertices.empty() || !data->polygons.empty()) {
    cleanData(data);
  }
  parseVAndF(file, data);
  normalizeVertices(data);
  file.close();
}

void Parser::cleanData(data *data) {
  data->vertices.clear();
  data->polygons.clear();
  data->polygons_normals.clear();
  data->normals.clear();
  data->max = -1;
}

void Parser::parseVAndF(std::ifstream &file, data *data) {
  std::string line;
  while (std::getline(file, line)) {
    if (line[0] == 'v' && line[1] == ' ') {
      std::stringstream ss(line.substr(2));
      std::string token;
      for (int j = 0; j < 3; j++) {
        ss >> token;
        double cord = std::stod(token);
        if (cord > data->max) {
          data->max = cord;
        }
        data->vertices.push_back(cord);
      }
    } else if (line[0] == 'f' && line[1] == ' ') {
      std::stringstream ss(line.substr(2));
      std::string token;
      data->polygons.push_back(std::vector<uint>(0));
      data->polygons_normals.push_back(std::vector<uint>(0));
      while (ss >> token) {
        int vertex = std::stoi(token);
        if (vertex <= 0) {
          vertex = data->vertices.size() / 3 + vertex + 1;
        } else if (vertex > (int)data->vertices.size() / 3) {
          vertex = vertex - data->vertices.size() / 3;
        }
        data->polygons[data->polygons.size() - 1].push_back(vertex - 1);
        if (std::count(token.begin(), token.end(), '/') > 1) {
          int normal = std::stoi(token.substr(token.find_last_of("/") + 1));
          data->polygons_normals[data->polygons_normals.size() - 1].push_back(
              normal);
        } else {
          data->polygons_normals[data->polygons_normals.size() - 1].push_back(
              1);
        }
      }
    } else if (line[0] == 'v' && line[1] == 'n' && line[2] == ' ') {
      std::stringstream ss(line.substr(3));
      std::string token;
      for (int j = 0; j < 3; j++) {
        ss >> token;
        data->normals.push_back(std::stod(token));
      }
    }
  }
}

void Parser::normalizeVertices(data *data) {
  if (data->max > 0.0) {
    for (size_t i = 0; i < data->vertices.size(); i++) {
      data->vertices[i] /= data->max;
    }
  }
}

}  // namespace s21
