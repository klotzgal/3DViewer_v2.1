#include "parser.h"

Parser::Parser() { std::cout << "Parser constructor" << std::endl; }

Parser::~Parser() { std::cout << "Parser destructor" << std::endl; }

void Parser::Parse(const std::string filename, data *data) {
  if (data->vertices != nullptr || data->facets != nullptr) {
    DataMemoryDeAllocation(data);
  }
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cout << "File not found" << std::endl;
    return;
  }
  CountVAndF(file, data);
  DataMemoryAllocation(data);
  file.clear();
  file.seekg(0);
  ParseVAndF(file, data);
  NormalizeVertices(data);
  file.close();
}

void Parser::CountVAndF(std::ifstream &file, data *data) {
  std::string line;
  while (std::getline(file, line)) {
    if (line[0] == 'v' && line[1] == ' ') {
      data->vertices_count++;
    } else if (line[0] == 'f' && line[1] == ' ') {
      data->facets_count++;
    }
  }
}

void Parser::DataMemoryAllocation(data *data) {
  data->vertices = new S21Matrix(data->vertices_count, 3);
  data->facets = new std::vector<data::Facets>(data->facets_count);
}

void Parser::DataMemoryDeAllocation(data *data) {
  delete data->vertices;
  delete data->facets;
  data->vertices_count = 0;
  data->facets_count = 0;
  data->vertices = nullptr;
  data->facets = nullptr;
  data->max = -1;
}

void Parser::ParseVAndF(std::ifstream &file, data *data) {
  std::string line;
  int v_ind = 0, f_ind = 0;
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
        (*data->vertices)(v_ind, j) = cord;
      }
      ++v_ind;
    } else if (line[0] == 'f' && line[1] == ' ') {
      std::stringstream ss(line.substr(2));
      std::string token;
      while (ss >> token) {
        int vertex = std::stoi(token);
        if (vertex < 0) {
          vertex = data->vertices_count + vertex + 1;
        } else if (vertex > (int)data->vertices_count) {
          vertex = vertex - data->vertices_count;
        }
        (*data->facets)[f_ind].vertexes.push_back(vertex);
        ++((*data->facets)[f_ind].numbers_of_vertexes_in_facets);
      }
      ++f_ind;
    }
  }
}

void Parser::NormalizeVertices(data *data) {
  if (data->max > 0.0) {
    for (size_t i = 0; i < data->vertices_count; i++) {
      for (int j = 0; j < 3; j++) {
        (*data->vertices)(i, j) /= data->max;
      }
    }
  }
}
