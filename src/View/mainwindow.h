#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QColorDialog>
#include <QMainWindow>
#include <QPainter>
#include <QSettings>
#include <QStyleOption>

#include "../Libs/gifimage/qgifimage.h"
#include "glwidget.h"
#include "stylehelper.h"

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
  void on_foto_clicked();
  void on_gif_clicked();

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

  // Display
  void on_display_type_currentIndexChanged(int index);
  void on_cord_mode_currentIndexChanged(int index);

  // Light
  void on_light_move_x_valueChanged(int value);
  void on_light_move_y_valueChanged(int value);
  void on_light_move_z_valueChanged(int value);

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

  // Gif
  void make_gif();

 protected:
  void paintEvent(QPaintEvent *event);

 private:
  Ui::MainWindow *ui;
  Controller *controller_;
  QSettings *settings_;
  QString gif_name_;
  QGifImage *gif_;
  QTimer *timer_;
  int frames_counter_ = 0;

  // Settings
  void loadSettings();
  void saveSettings();
  void setStyle();
};

#endif  // MAINWINDOW_H
