#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent, Controller *controller)
    : QOpenGLWidget{parent}, controller_(controller) {}

GLWidget::~GLWidget() {}

void GLWidget::initializeGL() {
  initializeOpenGLFunctions();
  glEnable(GL_DEPTH_TEST);  // depth buffer for z coordinate
}

void GLWidget::resizeGL(int w, int h) {
  w = h;
  glViewport(0, 0, w, h);
}

void GLWidget::paintGL() {
  glClearColor(bg_red, bg_green, bg_blue, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  setProjection();
  glEnableClientState(GL_VERTEX_ARRAY);  // enable open gl state
                                         // if (this->v_display_method != 0) {
  build_points();
  // }
  build_lines();
  glDisableClientState(GL_VERTEX_ARRAY);
}

void GLWidget::setProjection() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (this->projection_type == 0) {
    glFrustum(-1, 1, -1, 1, 1, 1000);
    glTranslatef(0, 0, -2);
    glRotatef(30, 1, 0, 0);
  } else {
    glOrtho(-1, 1, -1, 1, -1, 1000);
    glTranslatef(0, -1 / 2, 0);
  }
}

void GLWidget::buildPoints() {
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

void GLWidget::buildLines() {
  // if (this->edges_type == 1) {
  //   glEnable(GL_LINE_STIPPLE);
  //   glLineStipple(1, 0x00FF);
  // }
  glLineWidth(this->edges_thickness);
  glColor3f(this->e_red, this->e_green, this->e_blue);
  for (size_t i = 0; i < controller_->getPolygonsCount(); i++) {
    glDrawElements(GL_LINE_LOOP,
                   controller_->getPolygon(i).numbers_of_vertexes_in_polygons,
                   GL_UNSIGNED_INT, controller_->getPolygon(i).vertexes.data());
  }
  // lines that close
  // if (this->edges_type == 1) {
  //   glDisable(GL_LINE_STIPPLE);
  // }
}

void GLWidget::parseObj() {
  controller_->setFilename(
      "/home/klotzgal/Desktop/kl/S21_CPP/3DViewer_v2.0/src/Obj/cube.obj");
  //  /Users/klotzgal/Desktop/kl/3DViewer_v2.0/src/Obj/skull.obj
  //  /home/klotzgal/Desktop/kl/S21_CPP/3DViewer_v2.0/src/Obj/cube.obj
  try {
    controller_->Parse();
  } catch (const std::exception &e) {
    std::cerr << e.what() << "parse Error" << '\n';
    QMessageBox warning = QMessageBox();
    warning.setWindowTitle("Error");
    warning.setText("Please choose .obj file");
    warning.setIcon(QMessageBox::Warning);
    warning.exec();
  }
  update();
}
