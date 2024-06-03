#ifndef _WINDOW_
#define _WINDOW_

#include "../menu/menu.h"
#include "../header.h"

#include <QMainWindow>
#include <QResizeEvent>
#include <QTextEdit>
#include <QWidget>
#include <QTableWidget>
#include <QGridLayout>
#include <QPushButton>

typedef class Window : public QMainWindow {
  Q_OBJECT
  
private:
  QWidget m_mainWidget;
  QGridLayout m_layout;
  QTextEdit m_sqlCode;
  QTableWidget m_tableWidget;
  QPushButton m_injectButton;
  Menu m_menu;
  WindowSize m_size;
  std::vector<std::string> m_databaseName;
  std::vector<std::string> m_path;

public:
  Window(int *argc, char **argv);
  void resizeEvent(QResizeEvent *event) override;

  friend void getPathAndTables(Window *window, int *argc, char **argv);

} Window;

#endif
