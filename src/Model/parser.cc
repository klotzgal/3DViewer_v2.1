#include "parser.h"

Parser::Parser() { std::cout << "Parser constructor" << std::endl; }

Parser::~Parser() { std::cout << "Parser destructor" << std::endl; }

void Parser::Parse(const std::string filename, data *data) {
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
  data->vertices = S21Matrix(data->vertices_count, 3);
  data->facets.reserve(data->facets_count);
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
        data->vertices(v_ind, j) = std::stod(token);
      }
      ++v_ind;
    } else if (line[0] == 'f' && line[1] == ' ') {
      std::stringstream ss(line.substr(2));
      std::string token;
      while (ss >> token) {
        data->facets[f_ind].vertexes.push_back(std::stoi(token));
        ++(data->facets[f_ind].numbers_of_vertexes_in_facets);
      }
      ++f_ind;
    }
  }
}
