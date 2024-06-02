#include "handleSql.h"
#include "lexer/lexer.h"
#include "parser/parser.h"
#include "../error/error.h"
#include "sql.h"

#include <fstream>

bool findValueInVec(std::vector<std::string> *t_vec, std::string t_value) {
  for (std::string &val : *t_vec) {
    if (t_value == val) return true;
  }
  return false;
}

bool createTableFile(std::ofstream *file, CreateTable *table) {
  int count{ (int)table->title.size() - 1 };
  for (std::string &title : table->title) {
    if (count) {
      *file << title << ", ";
      count--;
    }
    else {
      *file << title;
      *file << "\n";
      count = (int)table->title.size() - 1;
    }
  }
  for (std::vector<std::string> &valVec : table->value) {
    for (std::string &val : valVec) {
      if (count) {
        *file << val << ", ";
        count--;
      }
      else {
        *file << val;
        *file << "\n";
        count = (int)table->title.size() - 1;
      }
    }
    
  }

  return false;
}

void createTable(Token *code, std::vector<std::string> *databaseName) {
  if (findValueInVec(databaseName, code->value[0].toStdString())) {
    PrintError error("Table already Exists");
    error.show();
    return (void)error.exec();
  }

  

  size_t size{ code->type.size() };
  if (size < 5) return;
  else if (code->type[3] != OPEN_PAREN) return;
  else if (code->type[(size - 1)] != CLOSE_PAREN) return;
  else if (code->type[2] != VALUE) return;
  
  unsigned int rowNum{};
  unsigned int posInValVec{ 1 };
  size_t sizeOfRow{};
  size_t tmpSize{};
  bool firstValue{ true };
  size_t sizeOfValVec{ code->value.size() };
  CreateTable table{};

  for (size_t i{ 4 }; i < (size - 1); i++) {
    if (code->type[i] == OPEN_PAREN || code->type[i] == CLOSE_PAREN) return;
    if (code->type[i] == KOMMA) {
      if (sizeOfRow < tmpSize) sizeOfRow = tmpSize;
      firstValue = false, rowNum = 0, tmpSize = 0;
      continue;
    }
    if (firstValue) {
      if (rowNum == 0) {
        if (posInValVec < sizeOfValVec) {
          table.title.push_back(code->value[posInValVec].toStdString());
        }
        else {
          table.title.push_back("");
        }
      }
      else {
        std::vector<std::string> tmp{};
        if (posInValVec < sizeOfValVec) {
          tmp.push_back(code->value[posInValVec].toStdString());
        }
        else {
          tmp.push_back("");
        }
        table.value.push_back(tmp);
      }
      posInValVec++, rowNum++, tmpSize++;
    } 
    else {
      if (rowNum == 0) {
        if (posInValVec < sizeOfValVec) {
          table.title.push_back(code->value[posInValVec].toStdString());
        }
        else {
          table.value[rowNum].push_back("");
        }
      }
      else {
        if (posInValVec < sizeOfValVec) {
          if ((rowNum + 1) > table.value.size()) {
            std::vector<std::string> tmp{ code->value[posInValVec].toStdString() };
            table.value.push_back(tmp);
          }
          else {
            table.value[rowNum].push_back(code->value[posInValVec].toStdString());
          }
        }
        else {
          if ((rowNum + 1) > table.value.size()) {
            std::vector<std::string> tmp{ "" };
            table.value.push_back(tmp);
          }
          else {
            table.value[rowNum].push_back("");
          }
        }
      }
      posInValVec++, rowNum++, tmpSize++;
    }
  }

  for (std::vector<std::string> &row : table.value) {
    size_t tmp{ row.size()};
    if (sizeOfRow > tmp) {
      for (size_t i{}; i < (sizeOfRow - tmp); i++) {
        row.push_back("");
      }
    }
  }

  std::string filename{ "../" + code->value[0].toStdString() + ".db" };
  std::ofstream file(filename);

  bool ret = createTableFile(&file, &table);
  if (ret) {
    PrintError error("Table couldn\'t be created");
    error.show();
    return (void)error.exec();
  }
  databaseName->push_back(filename.substr(3, (filename.find_last_of('.') - 3)));
}

void executeSqlCode(QString sql, std::vector<std::string> *databaseName) {
  std::vector<QString> tmp = lexer(sql);
  Token code = parser(&tmp);

  if (code.type.size() < 2) return;
  if (code.type[0] == CREATE && code.type[1] == TABLE) {
    createTable(&code, databaseName);
  }
}
