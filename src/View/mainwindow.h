#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "glwidget.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT
 public:
  explicit MainWindow(QWidget *parent = nullptr,
                      Controller *controller = nullptr);

  ~MainWindow();

 private slots:
  void on_load_model_clicked();
  void on_open_file_clicked();
 private:
  Ui::MainWindow *ui;
  Controller *controller_;
};

#endif  // MAINWINDOW_H
