#include "stylehelper.h"

QString StyleHelper::getButtonStyle() {
  return "background-color: qlineargradient(spread:pad, x1:1, y1:1, x2:1, "
         "y2:0, stop:0 rgba(30, 45, 58, 255), stop:1 rgba(49, 74, 95, 255));"
         "border-radius: 5%;";
}

QString StyleHelper::getFrameStyle() {
  return "QFrame {"
         "   border: 1px solid rgb(0, 0, 0);"
         "   background-color: qlineargradient(spread:pad, x1:1, y1:1, x2:1, "
         "y2:0, stop:0 rgba(73, 86, 100, 255), stop:1 rgba(57, 66, 76, 255));"
         //          "   background-color: qlineargradient(spread:pad, x1:1,
         //          y1:1, x2:1, " "y2:0, stop:0 rgba(22, 41, 50, 255), stop:1
         //          rgba(17, 33, 40, 255));"
         "}"
         "QLabel {"
         "   background: transparent;"
         "   border: none;"
         "}";
}

QString StyleHelper::getCentralWidgetStyle() {
  return "QFrame {"
         "   background-color: qlineargradient(spread:pad, x1:1, y1:1, x2:1, "
         "y2:0, stop:0 rgba(17, 33, 40, 255), stop:1 rgba(22, 41, 50, 255));"
         "   border: 1px solid rgb(0, 0, 0);"
         "   border-radius: 20%;"
         "}"
         "QLabel {"
         "    background: transparent;"
         "    border: none;"
         "}";
}
