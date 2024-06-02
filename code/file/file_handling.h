#ifndef _FILE_HANDLING_
#define _FILE_HANDLING_

#include "../header.h"

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>

// o - open, c - close
typedef class slFile : public QDialog {
  Q_OBJECT

private:
  QLineEdit m_fileName;
  QPushButton m_sl; // s - save, l - load
  QLabel m_text;
  QGridLayout m_layout;

public:
  slFile(QString title, WindowSize *t_size);

} slFile;

#endif
