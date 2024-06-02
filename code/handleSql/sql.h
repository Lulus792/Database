#ifndef _SQL_
#define _SQL_

#include <vector>
#include <QString>

typedef enum {
  CREATE,
  TABLE,
  SELECT,
  FROM,
  VALUE,
  OPEN_PAREN,
  CLOSE_PAREN,
  KOMMA,
} SQL;

typedef std::vector<SQL> _Vec;

typedef struct {
  _Vec type;
  std::vector<QString> value;
} Token;

#endif 

