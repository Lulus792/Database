#include "window/window.h"

#include <QApplication>

int main(int argc, char **argv) {

  QApplication app(argc, argv);
  Window window(&argc, argv);

  window.show();
  return app.exec();
}
