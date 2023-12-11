#include <QApplication>

#include "calcview.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  s21::CalcView mainWindow;
  mainWindow.setGeometry(0, 0, 741, 460);
  mainWindow.show();

  return a.exec();
}
