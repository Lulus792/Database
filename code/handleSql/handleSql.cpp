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

bool createTableFile(std::ofstream *file, 
                     std::vector<std::vector<std::string>> *table) {

  int count{ (int)(*table)[0].size() - 1 };

  for (std::vector<std::string> &valVec : *table) {
    for (std::string &val : valVec) {
      if (count) {
        *file << val << ", ";
        count--;
      }
      else {
        *file << val;
        *file << "\n";
        count = (int)(*table)[0].size() - 1;
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
  
  // tracks the position of the current row
  unsigned int rowNum{}; 

  // tracks the position for the value in code->value
  unsigned int posInValVec{ 1 }; 

  // in the first loop a new vector must be 
  // created for each row in table.value
  bool createNewVec{ true };

  // contains the size of the vector wich contains the values
  // for the table. Nessessary for checking if you try to acces
  // outside of the vector
  size_t sizeOfValVec{ code->value.size() };
  std::vector<std::vector<std::string>> table{};

  for (size_t i{ 4 }; i < (size - 1); i++) {
    if (code->type[i] == OPEN_PAREN || code->type[i] == CLOSE_PAREN) return;
    if (code->type[i] == KOMMA) {
      createNewVec = false, rowNum = 0;
      continue;
    }
    if (createNewVec) {
      std::vector<std::string> tmp{};
      if (posInValVec < sizeOfValVec) {
        tmp.push_back(code->value[posInValVec].toStdString());
      }
      else {
        tmp.push_back(" ");
      }
      table.push_back(tmp);
      posInValVec++, rowNum++;
    } 
    else {
      if (posInValVec < sizeOfValVec) {
        if (rowNum >= table.size()) {
          std::vector<std::string> tmp{ code->value[posInValVec].toStdString() };
          table.push_back(tmp);
        }
        else {
          table[rowNum].push_back(code->value[posInValVec].toStdString());
        }
      }
      else {
        if (rowNum >= table.size()) {
          std::vector<std::string> tmp{ " " };
          table.push_back(tmp);
        }
        else {
          table[rowNum].push_back(" ");
        }
      }
      posInValVec++, rowNum++;
    }
  }

  // tracks the maximum size of the rows
  size_t sizeOfRow{ table[0].size() };

  for (std::vector<std::string> &row : table) {
    if (sizeOfRow < row.size()) sizeOfRow = row.size();
  }

  for (std::vector<std::string> &row : table) {
    size_t tmp{ row.size() };

    if (sizeOfRow > tmp) {
      for (size_t i{}; i < (sizeOfRow - tmp); i++) {
        row.push_back(" ");
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
