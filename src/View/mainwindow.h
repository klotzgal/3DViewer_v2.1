#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QColorDialog>
#include <QMainWindow>
#include <QSettings>

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
  void on_render_model_clicked();
  void on_open_file_clicked();

  // Affine
  void on_scale_valueChanged(int value);
  void on_rotate_x_valueChanged(int value);
  void on_rotate_y_valueChanged(int value);
  void on_rotate_z_valueChanged(int value);
  void on_move_x_valueChanged(int value);
  void on_move_y_valueChanged(int value);
  void on_move_z_valueChanged(int value);

  // Projection
  void on_projection_type_currentIndexChanged(int index);

  // Color
  void on_bg_color_clicked();
  void on_vert_color_clicked();
  void on_edges_color_clicked();

  // Size
  void on_vert_size_valueChanged(int value);
  void on_edges_size_valueChanged(int value);

  // Type
  void on_vert_none_clicked();
  void on_vert_circle_clicked();
  void on_vert_square_clicked();
  void on_edges_solid_clicked();
  void on_edges_dashed_clicked();

 private:
  Ui::MainWindow *ui;
  Controller *controller_;
  QSettings *settings;

  // Settings
  void load_settings();
  void save_settings();
};

#endif  // MAINWINDOW_H
