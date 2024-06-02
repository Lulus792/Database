#ifndef _ERROR_
#define _ERROR_

#include <QErrorMessage>

typedef class PrintError : public QErrorMessage {

public:
  PrintError(QString message);
} PrintError;

#endif
