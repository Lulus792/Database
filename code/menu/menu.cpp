#include "menu.h"

Menu::Menu() {

  this->m_fileMenu.open.setText("Open");
  this->m_fileMenu.save.setText("Save");
  this->m_menu.setTitle("File");
  this->m_menu.addAction(&this->m_fileMenu.open);
  this->m_menu.addAction(&this->m_fileMenu.save);

  this->addMenu(&this->m_menu);

}

FileMenu *Menu::getActions() {
  return &this->m_fileMenu;
}
