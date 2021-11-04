#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[]) {

  QApplication app(argc, argv);

  MainWindow window;

  window.resize(300, 350);
  window.setWindowTitle("Main window");
  window.show();

  return app.exec();
}
