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
  Ui::MainWindow *ui;

  ~MainWindow();

 public slots:
  void on_load_model_clicked();

 private:
  Controller *controller_;
};

#endif  // MAINWINDOW_H
