#include "mainwindow.h"

#include "glwidget.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, Controller *controller)
    : QMainWindow{parent}, ui(new Ui::MainWindow), controller_(controller) {
  ui->setupUi(this);
  ui->GLWidget->setController(controller_);
  settings = new QSettings("School_21", "3D_Viewer", this);
  load_settings();
}

MainWindow::~MainWindow() {
  save_settings();
  delete settings;
  delete ui;
}

void MainWindow::load_settings() {
  // Projection
  ui->GLWidget->projection_type = settings->value("projection_type", 0).toInt();
  // Colors
  QColor c = settings->value("bg_color", QColor(0, 0, 0)).value<QColor>();
  ui->GLWidget->bg_color = c;
  ui->bg_color->setStyleSheet(
      "background-color: rgb(" + QString::number(c.red()) + "," +
      QString::number(c.green()) + "," + QString::number(c.blue()) + ")");
  setStyleSheet(
              "background-color: rgb(" + QString::number(c.red()) + "," +
              QString::number(c.green()) + "," + QString::number(c.blue()) + ")");
  c = settings->value("vert_color", QColor(1, 1, 1)).value<QColor>();
  ui->GLWidget->vert_color = c;
  ui->vert_color->setStyleSheet(
      "background-color: rgb(" + QString::number(c.red()) + "," +
      QString::number(c.green()) + "," + QString::number(c.blue()) + ")");
  c = settings->value("edges_color", QColor(1, 1, 1)).value<QColor>();
  ui->GLWidget->edges_color = c;
  ui->edges_color->setStyleSheet(
      "background-color: rgb(" + QString::number(c.red()) + "," +
      QString::number(c.green()) + "," + QString::number(c.blue()) + ")");
  // Size
  ui->GLWidget->vert_size = settings->value("vert_size", 1).toDouble();
  ui->vert_size->setValue(ui->GLWidget->vert_size);
  ui->GLWidget->edges_size = settings->value("edges_size", 1).toDouble();
  ui->edges_size->setValue(ui->GLWidget->edges_size);
  // Type
  ui->GLWidget->vert_type = settings->value("vert_type", 1).toDouble();
  if (ui->GLWidget->vert_type == 0) {
      ui->vert_none->setChecked(true);
  } else if (ui->GLWidget->vert_type == 1) {
      ui->vert_circle->setChecked(true);
  } else if (ui->GLWidget->vert_type == 2){
      ui->vert_square->setChecked(true);
  }
  ui->GLWidget->edges_type = settings->value("edges_type", 0).toDouble();
  if (ui->GLWidget->edges_type == 0) {
      ui->edges_solid->setChecked(true);
  } else if (ui->GLWidget->edges_type == 1) {
      ui->edges_dashed->setChecked(true);
  }
}

void MainWindow::save_settings() {
  settings->setValue("projection_type", ui->GLWidget->projection_type);
  settings->setValue("bg_color", ui->GLWidget->bg_color);
  settings->setValue("vert_color", ui->GLWidget->vert_color);
  settings->setValue("edges_color", ui->GLWidget->edges_color);
  settings->setValue("vert_size", ui->GLWidget->vert_size);
  settings->setValue("edges_size", ui->GLWidget->edges_size);
  settings->setValue("vert_type", ui->GLWidget->vert_type);
  settings->setValue("edges_type", ui->GLWidget->edges_type);
}

void MainWindow::on_render_model_clicked() {
  qDebug() << "Render";
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
  controller_->Rotate(k, 0, 0);
  ui->GLWidget->update();
}

void MainWindow::on_rotate_y_valueChanged(int value) {
  GLdouble k = (double)value - ui->GLWidget->rotate_y;
  qDebug() << "k =" << k;
  ui->GLWidget->rotate_y = value;
  controller_->Rotate(0, k, 0);
  ui->GLWidget->update();
}

void MainWindow::on_rotate_z_valueChanged(int value) {
  GLdouble k = (double)value - ui->GLWidget->rotate_z;
  qDebug() << "k =" << k;
  ui->GLWidget->rotate_z = value;
  controller_->Rotate(0, 0, k);
  ui->GLWidget->update();
}

void MainWindow::on_move_x_valueChanged(int value) {
  GLdouble k = ((double)value - ui->GLWidget->move_x) * 0.01;
  qDebug() << "k =" << k;
  ui->GLWidget->move_x = value;
  controller_->Move(k, 0, 0);
  ui->GLWidget->update();
}

void MainWindow::on_move_y_valueChanged(int value) {
  GLdouble k = ((double)value - ui->GLWidget->move_y) * 0.01;
  qDebug() << "k =" << k;
  ui->GLWidget->move_y = value;
  controller_->Move(0, k, 0);
  ui->GLWidget->update();
}

void MainWindow::on_move_z_valueChanged(int value) {
  GLdouble k = ((double)value - ui->GLWidget->move_z) * 0.01;
  qDebug() << "k =" << k;
  ui->GLWidget->move_z = value;
  controller_->Move(0, 0, k);
  ui->GLWidget->update();
}

void MainWindow::on_projection_type_currentIndexChanged(int index) {
  if (index == 0) {
    ui->GLWidget->projection_type = 0;
  } else if (index == 1) {
    ui->GLWidget->projection_type = 1;
  }
  ui->GLWidget->update();
}

void MainWindow::on_bg_color_clicked() {
  qDebug() << "bg_color";
  QColor bg_color =
      QColorDialog::getColor(Qt::white, ui->bg_tab, "Choose background color");
  if (bg_color.isValid()) {
    ui->GLWidget->bg_color = bg_color;
    QString style = "background-color: rgb(" +
            QString::number(bg_color.red()) + "," +
            QString::number(bg_color.green()) + "," +
            QString::number(bg_color.blue()) + ")";
    ui->bg_color->setStyleSheet(style);
    setStyleSheet(style);
    ui->GLWidget->update();
  }
}

void MainWindow::on_vert_color_clicked() {
  qDebug() << "vert_color";
  QColor vert_color = QColorDialog::getColor(Qt::white, ui->vert_tab,
                                             "Choose background color");
  if (vert_color.isValid()) {
    ui->GLWidget->vert_color = vert_color;
    ui->vert_color->setStyleSheet("background-color: rgb(" +
                                  QString::number(vert_color.red()) + "," +
                                  QString::number(vert_color.green()) + "," +
                                  QString::number(vert_color.blue()) + ")");
    ui->GLWidget->update();
  }
}

void MainWindow::on_edges_color_clicked() {
  qDebug() << "edges_color";
  QColor edges_color =
      QColorDialog::getColor(Qt::white, ui->edges_tab, "Choose edges color");
  if (edges_color.isValid()) {
    ui->GLWidget->edges_color = edges_color;
    ui->edges_color->setStyleSheet("background-color: rgb(" +
                                   QString::number(edges_color.red()) + "," +
                                   QString::number(edges_color.green()) + "," +
                                   QString::number(edges_color.blue()) + ")");
    ui->GLWidget->update();
  }
}

void MainWindow::on_vert_size_valueChanged(int value) {
  ui->GLWidget->vert_size = value;
  ui->GLWidget->update();
}

void MainWindow::on_edges_size_valueChanged(int value) {
  ui->GLWidget->edges_size = value;
  ui->GLWidget->update();
}

void MainWindow::on_vert_none_clicked() {
  qDebug() << "vert_none";
  ui->GLWidget->vert_type = 0;
  ui->GLWidget->update();
}

void MainWindow::on_vert_circle_clicked() {
  qDebug() << "vert_circle";
  ui->GLWidget->vert_type = 1;
  ui->GLWidget->update();
}

void MainWindow::on_vert_square_clicked() {
  qDebug() << "vert_square";
  ui->GLWidget->vert_type = 2;
  ui->GLWidget->update();
}

void MainWindow::on_edges_solid_clicked() {
  ui->GLWidget->edges_type = 0;
  ui->GLWidget->update();
}

void MainWindow::on_edges_dashed_clicked() {
  ui->GLWidget->edges_type = 1;
  ui->GLWidget->update();
}
