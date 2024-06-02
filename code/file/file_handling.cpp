#include "file_handling.h"

#define WIDTH_DIV   4
#define HEIGHT_DIV  15

slFile::slFile(QString title, WindowSize *t_size) {
 
  this->setWindowTitle(title);

  if ((t_size->width / WIDTH_DIV) < 400 || (t_size->height / HEIGHT_DIV) < 50) {
    this->resize(400, 50);
  }
  else {
    this->resize((t_size->width / WIDTH_DIV), (t_size->height / HEIGHT_DIV));
  }
  this->setLayout(&this->m_layout);

  this->m_text.setText("Filename:");
  this->m_sl.setText(title);

  this->m_layout.addWidget(&m_text, 0, 0, 1, 2);
  this->m_layout.addWidget(&m_fileName, 0, 2, 1, 10);
  this->m_layout.addWidget(&m_sl, 0, 12, 1, 3);

  this->connect(&m_sl, &QPushButton::pressed, [&]() -> void {
    this->close();
  });

}
