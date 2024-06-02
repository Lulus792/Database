#ifndef _FILE_MENU_
#define _FILE_MENU_

#include <QMenu>
#include <QMenuBar>
#include <QAction>

typedef struct {
  QAction open;
  QAction save;
} FileMenu;

typedef class Menu : public QMenuBar {
  Q_OBJECT

private:
  QMenu m_menu;
  FileMenu m_fileMenu;

public:
  Menu();
  FileMenu *getActions();

} Menu;

#endif
