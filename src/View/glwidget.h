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

  GLdouble vert_size = 1;
  GLdouble edges_size = 1;
  GLint projection_type = 0;
  GLint vert_type = 0;
  GLint edges_type = 0;
  QColor bg_color;
  QColor vert_color;
  QColor edges_color;
  /* 3D MODEL DATA END  */

  void setController(Controller *controller) { controller_ = controller; }

  // OPENGL
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

  void parseObj();

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
