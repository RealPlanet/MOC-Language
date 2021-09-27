#ifndef MOC_PARSER_H
#define MOC_PARSER_H
#include "../include/Token.h"

class Parser{
public:
	void start(TokenList* list, char* source);
};

#endif // MOC_PARSER_H