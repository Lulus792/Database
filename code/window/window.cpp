#include "window.h"
#include "../file/file_handling.h"
#include "../handleSql/handleSql.h"

#include <QGuiApplication>
#include <QScreen>

Window::Window(int *argc, char **argv) {

  for (size_t i{ 1 }; i < (size_t)(*argc); i++) {
    this->m_databaseName.push_back(argv[i]);
  }

  this->m_size.width = QGuiApplication::primaryScreen()->geometry().width();
  this->m_size.height = QGuiApplication::primaryScreen()->geometry().height();

  this->resize(this->m_size.width, this->m_size.height);
  this->m_injectButton.setText("Search");

  this->m_layout.addWidget(&this->m_sqlCode, 0, 2, 5, 14);
  this->m_layout.addWidget(&this->m_injectButton, 0, 16, 1, 1);
  this->m_layout.addWidget(&this->m_tableWidget, 5, 0, 20, 20);

  this->m_mainWidget.setLayout(&this->m_layout);
  this->setCentralWidget(&this->m_mainWidget);
  this->centralWidget()->layout()->setContentsMargins(0, 0, 0, 0);
  this->setMenuBar(&this->m_menu);

  this->connect(&this->m_menu.getActions()->open, &QAction::triggered, [&]() -> void {
    slFile loadFile("Open", &m_size);
    loadFile.show();
    return (void)loadFile.exec();
  });

  this->connect(&this->m_menu.getActions()->save, &QAction::triggered, [&]() -> void {
    slFile loadFile("Save", &m_size);
    loadFile.show();
    return (void)loadFile.exec();
  });

  this->connect(&this->m_injectButton, &QPushButton::pressed, [&]() ->void {
    executeSqlCode(this->m_sqlCode.toPlainText(), &this->m_databaseName);
  });

}

void Window::resizeEvent(QResizeEvent *event) {
  this->m_size.width = event->size().width();
  this->m_size.height = event->size().height();
}

