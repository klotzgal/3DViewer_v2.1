#include <QApplication>
#include <QStyle>

#include "View/mainwindow.h"

s21::Model *s21::Model::instance_ = nullptr;

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21::Model *m = s21::Model::getInstance();
  s21::Controller c(m);
  MainWindow w(nullptr, &c);
  w.show();
  return a.exec();
}
