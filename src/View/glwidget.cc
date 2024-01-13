#include "glwidget.h"

MyGLWidget::MyGLWidget(QWidget *parent, Controller *controller)
    : QOpenGLWidget{parent}, controller_(controller) {
    setMinimumSize(600, 600);
    setMaximumSize(1200, 1200);
}

MyGLWidget::~MyGLWidget() {}

void MyGLWidget::initializeGL() {
  initializeOpenGLFunctions();
  glEnable(GL_DEPTH_TEST);  // depth buffer for z coordinate
}

void MyGLWidget::resizeGL(int w, int h) {
//  w = h;
  glViewport(0, 0, w, h);
}

void MyGLWidget::paintGL() {
  glClearColor(bg_red, bg_green, bg_blue, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  setProjection();
  if (!controller_->isEmpty()) {
    glEnableClientState(GL_VERTEX_ARRAY);  // enable open gl state
    // if (this->v_display_method != 0) {
    buildPoints();
    // }
    buildLines();
    glDisableClientState(GL_VERTEX_ARRAY);
  }
}

void MyGLWidget::setProjection() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
//  if (this->projection_type == 0) {
//    glFrustum(-1, 1, -1, 1, 1, 1000);
//    glTranslatef(0, 0, -2);
//    glRotatef(30, 1, 0, 0);
//  } else {
//    glOrtho(-1, 1, -1, 1, -1, 1000);
//    glTranslatef(0, -1 / 2, 0);
//  }
}

void MyGLWidget::buildPoints() {
  if (this->v_display_method == 1) {
    glEnable(GL_POINT_SMOOTH);
  }
  glPointSize(this->vertices_size);
  glColor3f(this->v_red, this->v_green, this->v_blue);
  for (size_t i = 0; i < controller_->getVerticesCount(); i++) {
    GLdouble x = controller_->getX(i);
    GLdouble y = controller_->getY(i);
    GLdouble z = controller_->getZ(i);
    glBegin(GL_POINTS);
    glVertex3d(x, y, z);
    glEnd();
  }
  if (this->v_display_method == 1) {
    glDisable(GL_POINT_SMOOTH);
  }
}

void MyGLWidget::buildLines() {
  // if (this->edges_type == 1) {
  //   glEnable(GL_LINE_STIPPLE);
  //   glLineStipple(1, 0x00FF);
  // }

  glLineWidth(this->edges_thickness);
  glColor3f(this->e_red, this->e_green, this->e_blue);
  //  for (size_t i = 0; i < controller_->getPolygonsCount(); i++) {
  // controller_->getPolygon(0).numbers_of_vertexes_in_polygons

  for (size_t i = 0; i < controller_->getPolygonsCount(); ++i) {
    glBegin(GL_LINE_LOOP);
    for (size_t j = 0;
         j < controller_->getPolygon(i).numbers_of_vertexes_in_polygons; ++j) {
      GLint point = controller_->getPolygon(i).vertexes[j];
      GLdouble x = controller_->getX(point);
      GLdouble y = controller_->getY(point);
      GLdouble z = controller_->getZ(point);

      glVertex3d(x, y, z);
//            qDebug() << i << x << y << z;
    }
    glEnd();
  }

  //  }
  // lines that close
  // if (this->edges_type == 1) {
  //   glDisable(GL_LINE_STIPPLE);
  // }
}

void MyGLWidget::parseObj() {
//  controller_->setFilename(
//      "/home/klotzgal/Desktop/kl/S21_CPP/3DViewer_v2.0/src/Obj/skull.obj");
//  //  /Users/klotzgal/Desktop/kl/3DViewer_v2.0/src/Obj/skull.obj
//  //  /home/klotzgal/Desktop/kl/S21_CPP/3DViewer_v2.0/src/Obj/cube.obj
  try {
    controller_->Parse();
//    controller_->Scale(0.5);
  } catch (const std::exception &e) {
    std::cerr << e.what() << "parse Error" << '\n';
    QMessageBox warning = QMessageBox();
    warning.setWindowTitle("Error");
    warning.setText("Please choose .obj file");
    warning.setIcon(QMessageBox::Warning);
    warning.exec();
  }
}
