#include "mainwindow.h"

#include "glwidget.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, Controller *controller)
    : QMainWindow{parent}, ui(new Ui::MainWindow), controller_(controller) {
  ui->setupUi(this);
  ui->GLWidget->setController(controller_);
  settings_ = new QSettings("School_21", "3D_Viewer", this);
  //  setWindowFlags(Qt::FramelessWindowHint);
  timer_ = new QTimer(0);
  connect(timer_, SIGNAL(timeout()), this, SLOT(make_gif()));
  setStyle();
  loadSettings();
}

MainWindow::~MainWindow() {
  saveSettings();
  delete timer_;
  if (gif_ != nullptr) {
    delete gif_;
  }
  delete settings_;
  delete ui;
}

void MainWindow::loadSettings() {
  // Projection
  ui->GLWidget->projection_type =
      settings_->value("projection_type", 0).toInt();
  ui->projection_type->setCurrentIndex(ui->GLWidget->projection_type);
  // Colors
  QColor color = QColor("rgb(21, 30, 36)");
  QColor c = settings_->value("bg_color", color).value<QColor>();
  qDebug() << color.name() << color.HexArgb;
  ui->GLWidget->bg_color = c;
  ui->bg_color->setStyleSheet(
      "background-color: rgb(" % QString::number(c.red()) % "," %
      QString::number(c.green()) % "," % QString::number(c.blue()) % ")");
  c = settings_->value("vert_color", QColor(1, 1, 1)).value<QColor>();
  ui->GLWidget->vert_color = c;
  ui->vert_color->setStyleSheet(
      "background-color: rgb(" % QString::number(c.red()) % "," %
      QString::number(c.green()) % "," % QString::number(c.blue()) % ")");
  c = settings_->value("edges_color", QColor(1, 1, 1)).value<QColor>();
  ui->GLWidget->edges_color = c;
  ui->edges_color->setStyleSheet(
      "background-color: rgb(" % QString::number(c.red()) % "," %
      QString::number(c.green()) % "," % QString::number(c.blue()) % ")");
  // Size
  ui->GLWidget->vert_size = settings_->value("vert_size", 1).toDouble();
  ui->vert_size->setValue(ui->GLWidget->vert_size);
  ui->GLWidget->edges_size = settings_->value("edges_size", 1).toDouble();
  ui->edges_size->setValue(ui->GLWidget->edges_size);
  // Type
  ui->GLWidget->vert_type = settings_->value("vert_type", 1).toDouble();
  if (ui->GLWidget->vert_type == 0) {
    ui->vert_none->setChecked(true);
  } else if (ui->GLWidget->vert_type == 1) {
    ui->vert_circle->setChecked(true);
  } else if (ui->GLWidget->vert_type == 2) {
    ui->vert_square->setChecked(true);
  }
  ui->GLWidget->edges_type = settings_->value("edges_type", 0).toDouble();
  if (ui->GLWidget->edges_type == 0) {
    ui->edges_solid->setChecked(true);
  } else if (ui->GLWidget->edges_type == 1) {
    ui->edges_dashed->setChecked(true);
  }
  ui->GLWidget->display_type = settings_->value("display_type", 0).toInt();
  ui->display_type->setCurrentIndex(ui->GLWidget->display_type);
  ui->GLWidget->cord_mode = settings_->value("cord_mode", 1).toBool();
  ui->cord_mode->setCurrentIndex(ui->GLWidget->cord_mode);
}

void MainWindow::saveSettings() {
  settings_->setValue("projection_type", ui->GLWidget->projection_type);
  settings_->setValue("display_type", ui->GLWidget->display_type);
  settings_->setValue("cord_mode", ui->GLWidget->cord_mode);
  settings_->setValue("bg_color", ui->GLWidget->bg_color);
  settings_->setValue("vert_color", ui->GLWidget->vert_color);
  settings_->setValue("edges_color", ui->GLWidget->edges_color);
  settings_->setValue("vert_size", ui->GLWidget->vert_size);
  settings_->setValue("edges_size", ui->GLWidget->edges_size);
  settings_->setValue("vert_type", ui->GLWidget->vert_type);
  settings_->setValue("edges_type", ui->GLWidget->edges_type);

}

void MainWindow::paintEvent(QPaintEvent *event) {
  QStyleOption opt;
  opt.initFrom(this);
  QPainter p(this);
  style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
  QWidget::paintEvent(event);
}

void MainWindow::setStyle() {
  //    setWindowFlags(Qt::WindowType::FramelessWindowHint);
  //    setAttribute(Qt::WA_TranslucentBackground);
  //    setAutoFillBackground(true);
  setStyleSheet(
      "background-color: qlineargradient(spread:pad, x1:1, y1:0.613636, x2:1, "
      "y2:0, stop:0 rgba(11, 14, 17, 255), stop:1 rgba(15, 20, 25, 255));");
  ui->centralwidget->setStyleSheet(StyleHelper::getCentralWidgetStyle());

  ui->gif->setStyleSheet(StyleHelper::getButtonStyle() %
                         "color: rgb(196, 41, 31);" %
                         "border-image: url(:/res/gif_ico.svg);");
  ui->foto->setStyleSheet(StyleHelper::getButtonStyle() %
                          "border-image: url(:/res/photo_ico.svg);");
  ui->open_file->setStyleSheet(StyleHelper::getButtonStyle() %
                               "border-image: url(:/res/open.svg);");
  ui->render_model->setStyleSheet(StyleHelper::getButtonStyle());

  ui->record_frame->setStyleSheet(StyleHelper::getFrameStyle());
  ui->open_file_frame->setStyleSheet(StyleHelper::getFrameStyle());

  ui->view_frame->setStyleSheet(StyleHelper::getFrameStyle());
  ui->style_frame->setStyleSheet(StyleHelper::getFrameStyle());
  ui->bg_style_frame->setStyleSheet(StyleHelper::getFrameStyle());
  ui->manipulation_frame->setStyleSheet(StyleHelper::getFrameStyle());
}

void MainWindow::on_render_model_clicked() {
  qDebug() << "Render";
  ui->GLWidget->parseObj();
  ui->GLWidget->update();
}

void MainWindow::on_open_file_clicked() {
  QString filename = QFileDialog::getOpenFileName(
      this, tr("Open .obj file:"), "~/", tr("Obj Files (*.obj)"));
  qDebug() << filename;
  controller_->setFilename(filename);
  std::cout << controller_->getFilename() << std::endl;
  ui->label->setText(filename);
  QString name =
      filename.right(filename.size() - filename.lastIndexOf('/') - 1);
  ui->filename->setText(name.left(name.lastIndexOf('.')));
  ui->GLWidget->parseObj();
  ui->vert_count->setText(
      QString::number(controller_->getVertices().size() / 3));
  double edges_count = 0;
  for (size_t i = 0; i < controller_->getPolygonsCount(); ++i) {
    edges_count += controller_->getPolygon(i).size();
  }
  ui->edges_count->setText(QString::number(edges_count));
  ui->GLWidget->update();
}

void MainWindow::on_scale_valueChanged(int value) {
  GLdouble k = (double)value / ui->GLWidget->scale_val;
  //  qDebug() << "k =" << k;
  ui->GLWidget->scale_val = value;
  controller_->scale(k);
  ui->GLWidget->update();
}

void MainWindow::on_rotate_x_valueChanged(int value) {
  GLdouble k = (double)value - ui->GLWidget->rotate_x;
  //  qDebug() << "k =" << k;
  ui->GLWidget->rotate_x = value;
  controller_->rotate(k, 0, 0);
  ui->GLWidget->update();
}

void MainWindow::on_rotate_y_valueChanged(int value) {
  GLdouble k = (double)value - ui->GLWidget->rotate_y;
  //  qDebug() << "k =" << k;
  ui->GLWidget->rotate_y = value;
  controller_->rotate(0, k, 0);
  ui->GLWidget->update();
}

void MainWindow::on_rotate_z_valueChanged(int value) {
  GLdouble k = (double)value - ui->GLWidget->rotate_z;
  //  qDebug() << "k =" << k;
  ui->GLWidget->rotate_z = value;
  controller_->rotate(0, 0, k);
  ui->GLWidget->update();
}

void MainWindow::on_move_x_valueChanged(int value) {
  GLdouble k = ((double)value - ui->GLWidget->move_x) * 0.1;
  //  qDebug() << "k =" << k;
  ui->GLWidget->move_x = value;
  controller_->move(k, 0, 0);
  ui->GLWidget->update();
}

void MainWindow::on_move_y_valueChanged(int value) {
  GLdouble k = ((double)value - ui->GLWidget->move_y) * 0.1;
  //  qDebug() << "k =" << k;
  ui->GLWidget->move_y = value;
  controller_->move(0, k, 0);
  ui->GLWidget->update();
}

void MainWindow::on_move_z_valueChanged(int value) {
  GLdouble k = ((double)value - ui->GLWidget->move_z) * 0.1;
  //  qDebug() << "k =" << k;
  ui->GLWidget->move_z = value;
  controller_->move(0, 0, k);
  ui->GLWidget->update();
}

void MainWindow::on_projection_type_currentIndexChanged(int index) {
  ui->GLWidget->projection_type = index;
  ui->GLWidget->update();
}

void MainWindow::on_display_type_currentIndexChanged(int index) {
  ui->GLWidget->display_type = index;
  ui->GLWidget->update();
}

void MainWindow::on_cord_mode_currentIndexChanged(int index) {
  qDebug() << index;
  ui->GLWidget->cord_mode = index;
  ui->GLWidget->update();
}

void MainWindow::on_light_move_x_valueChanged(int value) {
  ui->GLWidget->light_pos[0] = value;
  ui->GLWidget->update();
}

void MainWindow::on_light_move_y_valueChanged(int value) {
  ui->GLWidget->light_pos[1] = value;
  ui->GLWidget->update();
}

void MainWindow::on_light_move_z_valueChanged(int value) {
  ui->GLWidget->light_pos[2] = value;
  ui->GLWidget->update();
}

void MainWindow::on_bg_color_clicked() {
  qDebug() << "bg_color";
  QColor bg_color =
      QColorDialog::getColor(Qt::white, ui->bg_tab, "Choose background color");
  if (bg_color.isValid()) {
    ui->GLWidget->bg_color = bg_color;
    QString style = "background-color: rgb(" % QString::number(bg_color.red()) %
                    "," % QString::number(bg_color.green()) % "," %
                    QString::number(bg_color.blue()) % ")";
    ui->bg_color->setStyleSheet(style);
    //    setStyleSheet(style);
    ui->GLWidget->update();
  }
}

void MainWindow::on_vert_color_clicked() {
  qDebug() << "vert_color";
  QColor vert_color = QColorDialog::getColor(Qt::white, ui->vert_tab,
                                             "Choose background color");
  if (vert_color.isValid()) {
    ui->GLWidget->vert_color = vert_color;
    ui->vert_color->setStyleSheet("background-color: rgb(" %
                                  QString::number(vert_color.red()) % "," %
                                  QString::number(vert_color.green()) % "," %
                                  QString::number(vert_color.blue()) % ")");
    ui->GLWidget->update();
  }
}

void MainWindow::on_edges_color_clicked() {
  qDebug() << "edges_color";
  QColor edges_color =
      QColorDialog::getColor(Qt::white, ui->edges_tab, "Choose edges color");
  if (edges_color.isValid()) {
    ui->GLWidget->edges_color = edges_color;
    ui->edges_color->setStyleSheet("background-color: rgb(" %
                                   QString::number(edges_color.red()) % "," %
                                   QString::number(edges_color.green()) % "," %
                                   QString::number(edges_color.blue()) % ")");
    ui->GLWidget->update();
  }
}

void MainWindow::on_vert_size_valueChanged(int value) {
  ui->GLWidget->vert_size = value;
  ui->GLWidget->update();
}

void MainWindow::on_edges_size_valueChanged(int value) {
  ui->GLWidget->edges_size = value;
  ui->GLWidget->update();
}

void MainWindow::on_vert_none_clicked() {
  qDebug() << "vert_none";
  ui->GLWidget->vert_type = 0;
  ui->GLWidget->update();
}

void MainWindow::on_vert_circle_clicked() {
  qDebug() << "vert_circle";
  ui->GLWidget->vert_type = 1;
  ui->GLWidget->update();
}

void MainWindow::on_vert_square_clicked() {
  qDebug() << "vert_square";
  ui->GLWidget->vert_type = 2;
  ui->GLWidget->update();
}

void MainWindow::on_edges_solid_clicked() {
  ui->GLWidget->edges_type = 0;
  ui->GLWidget->update();
}

void MainWindow::on_edges_dashed_clicked() {
  ui->GLWidget->edges_type = 1;
  ui->GLWidget->update();
}

void MainWindow::on_foto_clicked() {
  QFileDialog dialog(this);
  QDateTime current_date = QDateTime::currentDateTime();
  QString name_pattern =
      "ScreenShot" % current_date.toString("yyyy-MM-dd hh.mm.ss") % ".jpeg";
  QString image_name = dialog.getSaveFileName(
      this, tr("Save a screenshot"), name_pattern, tr("image (*.jpeg *.bmp)"));
  if (image_name.length() > 0) {
    QImage img = ui->GLWidget->grabFramebuffer();
    img.save(image_name);
    QMessageBox message;
    message.information(0, "", "Screenshot saved successfully");
  }
}

void MainWindow::on_gif_clicked() {
  QFileDialog dialog(this);
  QDateTime current_date = QDateTime::currentDateTime();
  QString name_pattern =
      "Gif" % current_date.toString("yyyy-MM-dd hh.mm.ss") % ".gif";
  gif_name_ = dialog.getSaveFileName(this, tr("Save a gif"), name_pattern,
                                     tr("image (*.gif)"));
  if (gif_name_.length() > 0) {
    ui->gif->setDisabled(true);
    gif_ = new QGifImage;
    gif_->setDefaultDelay(10);
    timer_->setInterval(100);
    timer_->start();
  }
}

void MainWindow::make_gif() {
  QImage img = ui->GLWidget->grabFramebuffer();
  img = img.scaled(QSize(640, 480));
  gif_->addFrame(img);
  if (frames_counter_ == 50) {
    timer_->stop();
    gif_->save(gif_name_);
    frames_counter_ = 0;
    QMessageBox message;
    message.information(0, "", "Gif saved successfully");
    delete gif_;
    gif_ = nullptr;
    ui->gif->setText("");
    ui->gif->setEnabled(true);
  }
  ++frames_counter_;
  if (!ui->gif->isEnabled()) {
    ui->gif->setText(QString::number(frames_counter_ / 10) % "s");
  }
}
