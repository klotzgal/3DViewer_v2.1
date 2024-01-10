#include "model.h"

Model::Model() : filename_(""), data_(new data) {
  std::cout << "Model constructor" << std::endl;
}

Model::~Model() {
  std::cout << "Model destructor" << std::endl;
  delete data_;
}

void Model::Parse() {
  parser_.Parse(filename_, data_);
  // data_->Print();
}
