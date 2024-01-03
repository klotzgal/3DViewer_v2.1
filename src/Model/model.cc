#include "model.h"

Model::Model() : data_(new data), filename_("") {
  std::cout << "Model constructor" << std::endl;
  std::cout << "Matrix: " << data_->vertices.GetRows() << std::endl;
}

Model::~Model() {
  std::cout << "Model destructor" << std::endl;
  delete data_;
}

void Model::Parse() {
  parser_.Parse(filename_, data_);
  data_->Print();
}