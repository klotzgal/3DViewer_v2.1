#include "mainwindow.h"

#include "glwidget.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, Controller *controller)
    : QMainWindow{parent}, ui(new Ui::MainWindow), controller_(controller) {
  ui->setupUi(this);
  ui->GLWidget->setController(controller_);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_load_model_clicked() { ui->GLWidget->parse_obj(); }
