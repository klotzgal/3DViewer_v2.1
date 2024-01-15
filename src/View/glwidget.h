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

#include <QFileDialog>
#include <QMessageBox>
#include <QOpenGLWidget>
#include <QWheelEvent>
#include <QWidget>
#include <QtOpenGL>
#include <iostream>

#include "../Controller/controller.h"

class MyGLWidget : public QOpenGLWidget, protected QOpenGLFunctions {
 public:
  explicit MyGLWidget(QWidget *parent = Q_NULLPTR,
                      Controller *controller = nullptr);

  /* 3D MODEL DATA START */
  GLdouble scale_val = 1;
  GLdouble rotate_x;
  GLdouble rotate_y;
  GLdouble rotate_z;
  GLdouble move_x;
  GLdouble move_y;
  GLdouble move_z;
  GLdouble vertices_size = 1;
  GLdouble edges_thickness = 1;
  GLint projection_type = 0;
  GLint v_display_method = 0;
  GLint edges_type = 0;
  GLdouble v_red = 1, v_green = 1, v_blue = 1;
  GLdouble e_red = 1, e_green = 1, e_blue = 1;
  GLdouble bg_red = 0, bg_green = 0, bg_blue = 0;
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

  // MouseMoveControl
  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void wheelEvent(QWheelEvent *event) override;

 private:
  ~MyGLWidget() override;
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
