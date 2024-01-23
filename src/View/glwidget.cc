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

    glVertexPointer(3, GL_DOUBLE, 0, controller_->getVertices().data());
    GLdouble **VERT = nullptr;
    glGetPointerv(GL_VERTEX_ARRAY_POINTER, (GLvoid**)VERT);
    glEnableClientState(GL_VERTEX_ARRAY);
    if (this->vert_type != 0) {
      buildPoints();
    }

    std::cout << "VERT = " << VERT << std::endl;
    if (VERT){
        for (size_t i = 0; i < controller_->getVertices().size(); ++i) {
            for (size_t j = 0; j < 3; ++j){
                std::cout << VERT[j][i] << " ";
            }
            std::cout << std::endl;
        }
    }
    qDebug() << glGetError();
    buildLines();
    glDisableClientState(GL_VERTEX_ARRAY);
  }
}

void MyGLWidget::setProjection() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (this->projection_type == 0) {
    glFrustum(-1, 1, -1, 1, 1, 1000);
    glTranslatef(0, 0, -4);
    glRotatef(30, 1, 0, 0);
  } else {
    glOrtho(-1, 1, -1, 1, -5, 1000);
    glTranslatef(0, -1 / 2, 0);
  }
}

void MyGLWidget::buildPoints() {
  if (vert_type == 1) {
    glEnable(GL_POINT_SMOOTH);
  }
  glPointSize(vert_size);
  glColor3f(vert_color.redF(), vert_color.greenF(), vert_color.blueF());

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
  glColor3f(edges_color.redF(), edges_color.greenF(), edges_color.blueF());

  for (size_t i = 0; i < controller_->getPolygonsCount(); ++i) {
    glDrawElements(GL_LINE_LOOP, controller_->getPolygon(i).size(),
                   GL_UNSIGNED_INT, controller_->getPolygon(i).data());
  }

  if (this->edges_type == 1) {
    glDisable(GL_LINE_STIPPLE);
  }
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
    controller_->rotate(-delta.y() * 0.5, delta.x() * 0.5, 0);
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
