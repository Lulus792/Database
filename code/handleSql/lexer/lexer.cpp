#include "lexer.h"

std::vector<QString> lexer(QString sql) {
  std::vector<QString> ret{};

  QString tmp{};
  for (QChar c : sql) {
    if (c == '\n') {
      if (tmp.length() == 0) continue;
      ret.push_back(tmp);
      tmp = "";
    } 
    else if (c == ' ') {
      if (tmp.length() == 0) continue;
      ret.push_back(tmp.toLower());
      tmp = "";
      continue;
    }
    else if (c == '(') {
      if (tmp.length() != 0) ret.push_back(tmp);
      ret.push_back("(");
      tmp = "";
      continue;
    }
    else if (c == ')') {
      if (tmp.length() != 0) ret.push_back(tmp);
      ret.push_back(")");
      tmp = "";
      continue;
    }
    else if (c == ',') {
      if (tmp.length() != 0) ret.push_back(tmp);
      ret.push_back(",");
      tmp = "";
      continue;
    }
    tmp += c;
  }
  if (tmp != "") {
    ret.push_back(tmp.toLower());
  }

  return ret;
}
