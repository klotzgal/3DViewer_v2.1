#ifndef CPP4_3DVIEWER_V2_0_SRC_MODEL_MODEL_H
#define CPP4_3DVIEWER_V2_0_SRC_MODEL_MODEL_H

#include <iostream>

#include "parser.h"

class Model {
 public:
  using data = Parser::data;
  Model();
  ~Model();
  void setFilename(const std::string &filename) { filename_ = filename; }
  std::string getFilename() const noexcept { return filename_; }
  void Parse();
  data *data_;

 private:
    std::string filename_;
  Parser parser_;
};

#endif  // CPP4_3DVIEWER_V2_0_SRC_MODEL_MODEL_H