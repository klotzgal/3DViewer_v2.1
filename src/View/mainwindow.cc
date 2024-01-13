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
