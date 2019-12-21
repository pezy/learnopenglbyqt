#include <QApplication>
#include <QSurfaceFormat>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  QSurfaceFormat fmt;
  fmt.setVersion(3, 3);
  fmt.setProfile(QSurfaceFormat::CoreProfile);
  QSurfaceFormat::setDefaultFormat(fmt);

  MainWindow w;
  w.show();
  return a.exec();
}
