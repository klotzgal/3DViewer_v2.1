#include "stylehelper.h"

QString StyleHelper::getButtonStyle() {
  return "background-color: qlineargradient(spread:pad, x1:1, y1:1, x2:1, "
         "y2:0, stop:0 rgba(30, 45, 58, 255), stop:1 rgba(49, 74, 95, 255));"
         "color: rgb(255, 255, 0);"
         "border-radius: 5%;";
}

QString StyleHelper::getFrameStyle() {
  return "QFrame {"
         "   border: 1px solid rgb(0, 0, 0);"
         "   border-bottom: none;"
         "   background-color: rgb(37, 48, 53);"
         "   border-radius: 0px;"
         "   border-top-left-radius: 20px;"
         "   border-top-right-radius: 20px;"
         "}"
         "QLabel {"
         "   background: transparent;"
         "   border: none;"
         "}";
}

QString StyleHelper::getCentralWidgetStyle() {
  return "QFrame {"
         "color: rgb(255, 255, 0);"
         "background-color: rgb(37, 48, 53);"
         "   border: 1px solid rgb(0, 0, 0);"
         "   border-radius: 20px;"
         "}"
         "QLabel {"
         "    background: transparent;"
         "    border: none;"
         "}";
}
