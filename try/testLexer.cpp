#include <QString>
#include "../code/handleSql/lexer/lexer.h"
#include <iostream>

int main() {
  QString tmp = "Test This\n Out just for fun";
  std::vector<QString> res = lexer(tmp);
  for (QString &s : res) {
    std::cout << s.toStdString() << "\n";
  }
}
