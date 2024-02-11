#include "glwidget.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../Libs/stb_image.h"

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
  bool isLight = true;
  setProjection();
  if (cord_mode) {
    cordMode();
  }
  if (isLight || display_type == 1) {
    setLightning();
  }
  if (!controller_->isEmpty()) {
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnable(GL_TEXTURE_2D);
    setTextures();
    glVertexPointer(3, GL_DOUBLE, 0, controller_->getVertices().data());
    // GLfloat text_cord[] = {0, 0, 1, 0, 1, 1, 0, 1};
    glTexCoordPointer(2, GL_FLOAT, 0, controller_->getTextures().data());
    if (isLight && display_type == 2) {
      glEnableClientState(GL_NORMAL_ARRAY);
      glNormalPointer(GL_DOUBLE, 0, controller_->getAveragedNormals().data());
    }

    if (this->vert_type != 0) {
      buildPoints();
    }

    buildLines();
    if (isLight && display_type == 2) {
      glDisableClientState(GL_NORMAL_ARRAY);
    }
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);

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
  // if (cord_mode) {
  glEnable(GL_POINT_SMOOTH);
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, &light_pos);
  glColor3f(1, 1, 1);
  glPointSize(20);
  glDrawArrays(GL_POINTS, 0, 1);
  glDisableClientState(GL_VERTEX_ARRAY);
  // }
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_NORMALIZE);

  glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
  // glLightfv(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0);
  // glLightfv(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.0);
  // glLightfv(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.0);
}

void MyGLWidget::setTextures() {
  // glEnable(GL_TEXTURE_2D);
  GLuint texture;
  GLint width = 0, height = 0, cnt = 0;
  // struct {
  //   GLchar r, g, b;
  // } data[2][2];
  // data[0][0].r = 255;
  // data[1][0].g = 255;
  // data[1][1].b = 255;
  // data[0][1].r = 255;
  // data[0][1].g = 255;
  stbi_set_flip_vertically_on_load(true);
  unsigned char *data2 = stbi_load(
      "/home/klotzgal/Desktop/kl/S21_CPP/3DViewer_v2.0/src/texture.bmp", &width,
      &height, &cnt, 0);
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexImage2D(GL_TEXTURE_2D, 0, cnt == 4 ? GL_RGBA : GL_RGB, width, height, 0,
               GL_RGB, GL_UNSIGNED_BYTE, data2);
  qDebug() << "glTexImage2D" << width << height << cnt;
  stbi_image_free(data2);

  // glBindTexture(GL_TEXTURE_2D, 0);
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
      std::vector<double> normal = controller_->calcFloatNormal(i);
      glNormal3d(normal[0], normal[1], normal[2]);
    }
    glDrawElements(type, polygon.size(), GL_UNSIGNED_INT, polygon.data());
  }

  if (this->edges_type == 1) {
    glDisable(GL_LINE_STIPPLE);
  }
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
