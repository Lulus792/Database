#include "parser.h"
#include <iostream>

Token parser(std::vector<QString> *tmp) {
  Token ret;

  for (QString &s : *tmp) {
    if (s == "create") ret.type.push_back(CREATE);
    else if (s == "table") ret.type.push_back(TABLE);
    else if (s == "(") ret.type.push_back(OPEN_PAREN);
    else if (s == ")") ret.type.push_back(CLOSE_PAREN);
    else if (s == ",") ret.type.push_back(KOMMA);
    else if (s == "select") ret.type.push_back(SELECT);
    else if (s == "from") ret.type.push_back(FROM);
    else {
      ret.type.push_back(VALUE);
      ret.value.push_back(s);
    }
  }

  return ret;
}

void printParsedInfo(Token *code) {
  
  unsigned int i{};
  for (SQL &val : code->type) {
    switch(val) {
      case CREATE:
        std::cout << "CREATE\n";
        break;
      case TABLE:
        std::cout << "TABLE\n";
        break;
      case SELECT:
        std::cout << "SELECT\n";
        break;
      case FROM:
        std::cout << "FROM\n";
        break;
      case VALUE:
        std::cout << code->value[i].toStdString() << "\n";
        i++;
        break;
      case OPEN_PAREN:
        std::cout << "OPEN_PAREN\n";
        break;
      case CLOSE_PAREN:
        std::cout << "CLOSE_PAREN\n";
        break;
      case KOMMA:
        std::cout << "KOMMA\n";
        break;
    }
  }
}

