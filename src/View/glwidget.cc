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
  setFixedWidth(h);
  glViewport(0, 0, w, h);
}

void MyGLWidget::paintGL() {
  glClearColor(bg_color.redF(), bg_color.greenF(), bg_color.blueF(),
               bg_color.alphaF());
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  setProjection();
  if (!controller_->isEmpty()) {
    if (this->vert_type != 0) {
      buildPoints();
    }
    buildLines();
  }
}

void MyGLWidget::setProjection() {
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

void MyGLWidget::buildPoints() {
  if (vert_type == 1) {
    glEnable(GL_POINT_SMOOTH);
  }
  glPointSize(vert_size);
  glColor3f(vert_color.redF(), vert_color.greenF(), vert_color.blueF());
  for (size_t i = 0; i < controller_->getVerticesCount(); i++) {
    GLdouble x = controller_->getX(i);
    GLdouble y = controller_->getY(i);
    GLdouble z = controller_->getZ(i);
    glBegin(GL_POINTS);
    glVertex3d(x, y, z);
    glEnd();
  }
  if (this->vert_type == 1) {
    glDisable(GL_POINT_SMOOTH);
  }
}

void MyGLWidget::buildLines() {
  if (this->edges_type == 1) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x00FF);
  }

  glLineWidth(edges_size);
  glColor3f(edges_color.redF(), edges_color.greenF(), edges_color.blueF());

  for (size_t i = 0; i < controller_->getPolygonsCount(); ++i) {
    glBegin(GL_LINE_LOOP);
    for (size_t j = 0; j < controller_->getPolygon(i).size(); ++j) {
      GLint point = controller_->getPolygon(i)[j];
      GLdouble x = controller_->getX(point);
      GLdouble y = controller_->getY(point);
      GLdouble z = controller_->getZ(point);

      glVertex3d(x, y, z);
      //            qDebug() << i << x << y << z;
    }
    glEnd();
  }
  if (this->edges_type == 1) {
    glDisable(GL_LINE_STIPPLE);
  }
}

void MyGLWidget::parseObj() {
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
}

void MyGLWidget::mousePressEvent(QMouseEvent *event) {
  cur_pos = event->globalPosition().toPoint();
}

void MyGLWidget::mouseMoveEvent(QMouseEvent *event) {
  if (controller_->isEmpty()) {
    return;
  }
  QPoint delta = cur_pos - event->globalPosition().toPoint();
  cur_pos = event->globalPosition().toPoint();
  qDebug() << delta.x() * 0.5 << delta.y() * 0.5;
  if (event->buttons() & Qt::LeftButton) {
    controller_->Rotate(-delta.y() * 0.5, -delta.x() * 0.5, 0);
  } else if (event->buttons() & Qt::RightButton) {
    controller_->Move(-delta.x() * 0.002, delta.y() * 0.002, 0);
  }
  update();
}

void MyGLWidget::wheelEvent(QWheelEvent *event) {
  if (controller_->isEmpty()) {
    return;
  }
  if (event->angleDelta().y() < 0) {
    controller_->Scale(0.9);
  } else {
    controller_->Scale(1.1);
  }

  update();
}
