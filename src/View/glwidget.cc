#include "glwidget.h"

MyGLWidget::MyGLWidget(QWidget *parent, Controller *controller)
    : QOpenGLWidget{parent}, controller_(controller) {}

MyGLWidget::~MyGLWidget() {}

void MyGLWidget::initializeGL() {
  initializeOpenGLFunctions();
  glEnable(GL_DEPTH_TEST);  // depth buffer for z coordinate
}

void MyGLWidget::resizeGL(int w, int h) { glViewport(0, 0, w, h); }

void MyGLWidget::paintGL() {
  glClearColor(bg_color.redF(), bg_color.greenF(), bg_color.blueF(), 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  bool isLight = controller_->isHaveNormals();
  setProjection();
  if (cord_mode) {
    cordMode();
  }
  if (isLight || display_type == 1) {
    setLightning();
  }
  if (!controller_->isEmpty()) {
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_DOUBLE, 0, controller_->getVertices().data());

    if (isLight && display_type == 2) {
      glEnableClientState(GL_NORMAL_ARRAY);
      glNormalPointer(GL_DOUBLE, 0, controller_->getNormals().data());
    }

    if (this->vert_type != 0) {
      buildPoints();
    }

    buildLines();
    if (isLight && display_type == 2) {
      glDisableClientState(GL_NORMAL_ARRAY);
    }
    glDisableClientState(GL_VERTEX_ARRAY);
  }
}

void MyGLWidget::setProjection() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  GLdouble k = (double)width() / height();
  if (this->projection_type == 0) {
    glFrustum(-k, k, -1, 1, 1, 1000);
    glTranslatef(0, 0, -4);
  } else {
    glOrtho(-k, k, -1, 1, -5, 1000);
    glTranslatef(0, 0, -4);
  }
}

void MyGLWidget::setLightning() {
  if (cord_mode) {
    glEnable(GL_POINT_SMOOTH);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, &light_pos);
    glColor3f(1, 1, 1);
    glPointSize(20);
    glDrawArrays(GL_POINTS, 0, 1);
    glDisableClientState(GL_VERTEX_ARRAY);
  }
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_NORMALIZE);

  glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
}

void MyGLWidget::buildPoints() {
  if (vert_type == 1) {
    glEnable(GL_POINT_SMOOTH);
  }
  glPointSize(vert_size);
  glColor4f(vert_color.redF(), vert_color.greenF(), vert_color.blueF(), 1);

  glDrawArrays(GL_POINTS, 0, controller_->getVertices().size() / 3);

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
  glColor4f(edges_color.redF(), edges_color.greenF(), edges_color.blueF(), 1);

  auto type = display_type ? GL_POLYGON : GL_LINE_LOOP;
  for (size_t i = 0; i < controller_->getPolygonsCount(); ++i) {
    std::vector<uint> polygon = controller_->getPolygon(i);
    if (display_type == 1) {
      setPolygonNormal(polygon);
    }
    glDrawElements(type, polygon.size(), GL_UNSIGNED_INT, polygon.data());
  }

  if (this->edges_type == 1) {
    glDisable(GL_LINE_STIPPLE);
  }
}

void MyGLWidget::setPolygonNormal(std::vector<uint> &polygon) {
  std::vector<double>
      v1 = {controller_->getX(polygon[1]) - controller_->getX(polygon[0]),
            controller_->getY(polygon[1]) - controller_->getY(polygon[0]),
            controller_->getZ(polygon[1]) - controller_->getZ(polygon[0])},
      v2 = {controller_->getX(polygon[2]) - controller_->getX(polygon[1]),
            controller_->getY(polygon[2]) - controller_->getY(polygon[1]),
            controller_->getZ(polygon[2]) - controller_->getZ(polygon[1])};
  GLfloat nx = v1[1] * v2[2] - v1[2] * v2[1];
  GLfloat ny = v1[2] * v2[0] - v1[0] * v2[2];
  GLfloat nz = v1[0] * v2[1] - v1[1] * v2[0];
  GLfloat length = sqrt(nx * nx + ny * ny + nz * nz);
  nx /= length;
  ny /= length;
  nz /= length;
  glNormal3f(nx, ny, nz);
}

void MyGLWidget::cordMode() {
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);
  glRotatef(30, 1, 0, 0);
  glRotatef(-10, 0, 1, 0);
  GLfloat cord_vert[] = {10, 0,   0, -10, 0, 0,  0, 10, 0,
                         0,  -10, 0, 0,   0, 10, 0, 0,  -10};
  GLfloat cord_colors[] = {1, 0, 0, 1, 0, 0, 0, 1, 0,
                           0, 1, 0, 0, 0, 1, 0, 0, 1};
  glVertexPointer(3, GL_FLOAT, 0, &cord_vert);
  glColorPointer(3, GL_FLOAT, 0, &cord_colors);
  glLineWidth(2);
  glDrawArrays(GL_LINES, 0, 6);
  glDisableClientState(GL_COLOR_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);
}

void MyGLWidget::parseObj() {
  try {
    controller_->parse();
    controller_->print();
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
    controller_->rotate(delta.y() * 0.5, -delta.x() * 0.5, 0);
  } else if (event->buttons() & Qt::RightButton) {
    controller_->move(-delta.x() * 0.002, delta.y() * 0.002, 0);
  }
  update();
}

void MyGLWidget::wheelEvent(QWheelEvent *event) {
  if (controller_->isEmpty()) {
    return;
  }
  if (event->angleDelta().y() < 0) {
    controller_->scale(0.9);
  } else {
    controller_->scale(1.1);
  }

  update();
}
