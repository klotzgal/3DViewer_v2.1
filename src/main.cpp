#include <QApplication>

#include "View/mainwindow.h"

Model *Model::instance_ = nullptr;

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  Model *m = Model::getInstance();
  Controller c(m);
  MainWindow w(nullptr, &c);
  w.show();
  return a.exec();
}
