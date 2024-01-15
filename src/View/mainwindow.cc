#include "mainwindow.h"

#include "glwidget.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, Controller *controller)
    : QMainWindow{parent}, ui(new Ui::MainWindow), controller_(controller) {
  ui->setupUi(this);
  ui->GLWidget->setController(controller_);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_load_model_clicked() {
  ui->GLWidget->parseObj();
  ui->GLWidget->update();
}

void MainWindow::on_open_file_clicked() {
  QString filename = QFileDialog::getOpenFileName(
      this, tr("Open .obj file:"), "~/", tr("Obj Files (*.obj)"));
  qDebug() << filename;
  controller_->setFilename(filename);
  std::cout << controller_->getFilename() << std::endl;
  ui->label->setText(filename);
  ui->GLWidget->parseObj();
  ui->GLWidget->update();
}

void MainWindow::on_scale_valueChanged(int value) {
  GLdouble k = (double)value / ui->GLWidget->scale_val;
  qDebug() << "k =" << k;
  ui->GLWidget->scale_val = value;
  controller_->Scale(k);
  ui->GLWidget->update();
}

void MainWindow::on_rotate_x_valueChanged(int value) {
  GLdouble k = (double)value - ui->GLWidget->rotate_x;
  qDebug() << "k =" << k;
  ui->GLWidget->rotate_x = value;
  controller_->Rotate('x', k);
  ui->GLWidget->update();
}

void MainWindow::on_rotate_y_valueChanged(int value) {
  GLdouble k = (double)value - ui->GLWidget->rotate_y;
  qDebug() << "k =" << k;
  ui->GLWidget->rotate_y = value;
  controller_->Rotate('y', k);
  ui->GLWidget->update();
}

void MainWindow::on_rotate_z_valueChanged(int value) {
  GLdouble k = (double)value - ui->GLWidget->rotate_z;
  qDebug() << "k =" << k;
  ui->GLWidget->rotate_z = value;
  controller_->Rotate('z', k);
  ui->GLWidget->update();
}

void MainWindow::on_move_x_valueChanged(int value) {
  GLdouble k = ((double)value - ui->GLWidget->move_x) * 0.01;
  qDebug() << "k =" << k;
  ui->GLWidget->move_x = value;
  controller_->Move('x', k);
  ui->GLWidget->update();
}

void MainWindow::on_move_y_valueChanged(int value) {
  GLdouble k = ((double)value - ui->GLWidget->move_y) * 0.01;
  qDebug() << "k =" << k;
  ui->GLWidget->move_y = value;
  controller_->Move('y', k);
  ui->GLWidget->update();
}

void MainWindow::on_move_z_valueChanged(int value) {
  GLdouble k = ((double)value - ui->GLWidget->move_z) * 0.01;
  qDebug() << "k =" << k;
  ui->GLWidget->move_z = value;
  controller_->Move('z', k);
  ui->GLWidget->update();
}
