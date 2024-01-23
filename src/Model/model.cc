#include "model.h"

Model::Model() : filename_(""), data_(new data) {}

Model::~Model() { delete data_; }

void Model::parse() {
  parser_.parse(filename_, data_);
  // data_->Print();
}
