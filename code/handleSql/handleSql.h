#ifndef _HANDLE_SQL_
#define _HANDLE_SQL_

#include <QString>

typedef struct {
  std::vector<std::string> title;
  std::vector<std::vector<std::string>> value;
} CreateTable;

void executeSqlCode(QString sql, std::vector<std::string> *databaseName);

#endif
