#ifndef GLWIDGET_H
#define GLWIDGET_H

#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif

#include <QMessageBox>
#include <QOpenGLWidget>
#include <QWheelEvent>
#include <QWidget>
#include <QtOpenGL>
#include <iostream>

#include "../Controller/controller.h"

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions {
 public:
  explicit GLWidget(QWidget *parent = Q_NULLPTR,
                    Controller *controller = nullptr);

  /* 3D MODEL DATA START */
  double scale_val = 50;
  double rotate_x;
  double rotate_y;
  double rotate_z;
  double translate_x;
  double translate_y;
  double translate_z;
  double vertices_size = 1;
  double edges_thickness = 1;
  int projection_type = 0;
  int v_display_method = 0;
  int edges_type = 0;
  double v_red = 1, v_green = 1, v_blue = 1;
  double e_red = 1, e_green = 1, e_blue = 1;
  double bg_red = 0, bg_green = 0, bg_blue = 0;
  /* 3D MODEL DATA END  */

  // 3D OBJ DATA
  char *filename;
  // obj_data data = {0, NULL, 0, NULL};

  // OPENGL
  void setController(Controller *controller) { controller_ = controller; }
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

  void parseObj();

  GLfloat normalize_coef;

  // // MouseMoveControl
  // void mousePressEvent(QMouseEvent *event) override;
  // void mouseMoveEvent(QMouseEvent *event) override;
  // void wheelEvent(QWheelEvent *event) override;

 private:
  ~GLWidget() override;
  QPoint cur_pos;
  QPoint new_pos;
  // void render_ui_stats(); ???
  void setProjection();
  void buildLines();
  void buildPoints();
  Controller *controller_;

 signals:
};

#endif  // GLWIDGET_H
