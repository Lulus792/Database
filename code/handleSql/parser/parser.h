#ifndef _PARSER_
#define _PARSER_

#include "../sql.h"
#include <QString>

Token parser(std::vector<QString> *tmp); 

void printParsedInfo(Token *code);

#endif
