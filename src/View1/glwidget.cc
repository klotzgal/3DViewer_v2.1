#include "glwidget.h"

Model *Model::instance_ = nullptr;

GlWidget::GlWidget(QWidget *parent) : QOpenGLWidget{parent} {
  model = Model::getInstance();
  model->setFilename(
      "/home/klotzgal/Desktop/kl/S21_CPP/3DViewer_v2.0/src/Obj/cube.obj");
  //  /Users/klotzgal/Desktop/kl/3DViewer_v2.0/src/Obj/cube.obj
  //  /home/klotzgal/Desktop/kl/S21_CPP/3DViewer_v2.0/src/Obj/cube.obj
}

GlWidget::~GlWidget() {}

void GlWidget::initializeGL() {
  initializeOpenGLFunctions();
  glEnable(GL_DEPTH_TEST);  // depth buffer for z coordinate
}

void GlWidget::paintGL() {
  glClearColor(bg_red, bg_green, bg_blue, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // glVertexPointer(
  //     3, GL_DOUBLE, 0,
  //     model->getVertices().matrix_);  // number of coordinates per vertex,
  //     type
  // of data in array, distance between
  // vertices in array, pointer to array
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (this->projection_type == 0) {
    glFrustum(-1 * normalize_coef, 1 * normalize_coef, -1 * normalize_coef,
              1 * normalize_coef, normalize_coef, 1000 * normalize_coef);
    glTranslatef(0, 0, -2 * normalize_coef);
    glRotatef(30, 1, 0, 0);
  } else {
    glOrtho(-1 * normalize_coef, 1 * normalize_coef, -1 * normalize_coef,
            1 * normalize_coef, -1 * normalize_coef, 1000 * normalize_coef);
    glTranslatef(0, -normalize_coef / 2, 0);
  }
  glEnableClientState(GL_VERTEX_ARRAY);  // enable open gl state
                                         // if (this->v_display_method != 0) {
  build_points();
  // }
  // build_lines();
  glDisableClientState(GL_VERTEX_ARRAY);
}

void GlWidget::parse_obj() {
  // data_destructor(&this->data);
  // data = {0, NULL, 0, NULL};
  if (this->filename[0] != '\0') {
    model->setFilename(this->filename);
    try {
      model->Parse();
    } catch (const std::exception &e) {
      std::cerr << e.what() << "parse Error" << '\n';
    }
    set_normalize_coef();
    update();
  } else {
    QMessageBox warning = QMessageBox();
    warning.setWindowTitle("Error");
    warning.setText("Please choose .obj file");
    warning.setIcon(QMessageBox::Warning);
    warning.exec();
  }
}

void GlWidget::set_normalize_coef() {
  normalize_coef = -10;  // scarecrow

  for (size_t i = 0; i < model->getVerticesCount() * 3; i++) {
    if (abs(model->getVertices().matrix_[i]) > normalize_coef) {
      normalize_coef = abs(model->getVertices().matrix_[i]);
    }
  }
}

// void GlWidget::build_lines() {
//   if (this->edges_type == 1) {
//     glEnable(GL_LINE_STIPPLE);
//     glLineStipple(1, 0x00FF);
//   }
//   glLineWidth(this->edges_thickness);
//   glColor3f(this->e_red, this->e_green, this->e_blue);
//   glDrawElements(GL_LINES, data.vertex_indices_count * 2, GL_UNSIGNED_INT,
//                  data.vertex_indices_arr);  // multiply by two because we
//                  draw
//                                             // lines that close
//   if (this->edges_type == 1) {
//     glDisable(GL_LINE_STIPPLE);
//   }
// }

void GlWidget::build_points() {
  if (this->v_display_method == 1) {
    glEnable(GL_POINT_SMOOTH);
  }
  glPointSize(this->vertices_size);
  glColor3f(this->v_red, this->v_green, this->v_blue);
  // glDrawArrays(GL_POINTS, 0, model->getVerticesCount());
  for (size_t i = 0; i < model->getVerticesCount(); i++) {
    GLfloat x = model->getVertices()(i, 0);
    GLfloat y = model->getVertices()(i, 1);
    GLfloat z = model->getVertices()(i, 2);
    glBegin(GL_POINTS);
    glVertex3f(x, y, z);
    glEnd();
  }
  if (this->v_display_method == 1) {
    glDisable(GL_POINT_SMOOTH);
  }
}

// void GlWidget::mouseMoveEvent(QMouseEvent *event) {
//   new_pos = QPoint(event->globalPosition().toPoint() - cur_pos);

//   if (event->buttons() & Qt::LeftButton) {
//     move_X(&this->data, new_pos.x() * this->normalize_coef / 5000);
//     move_Y(&this->data, -new_pos.y() * this->normalize_coef / 5000);
//     update();
//   } else if (event->buttons() & Qt::RightButton) {
//     rotate_X(&this->data, -new_pos.y() * 0.005);
//     rotate_Y(&this->data, new_pos.x() * 0.005);
//     update();
//   }
// }

// void GlWidget::wheelEvent(QWheelEvent *event) {
//   QPoint numDegrees = event->angleDelta() / 120;
//   double step = normalize_coef / 10;
//   double scale_tmp = scale_val;
//   if ((int)(scale_val + numDegrees.y() * step) > 0) {
//     scale_val += numDegrees.y() * step;
//     scale(&this->data, scale_val / scale_tmp);
//     update();
//   }
// }

// void GlWidget::mousePressEvent(QMouseEvent *event) {
//   cur_pos = event->globalPosition().toPoint();
// }
