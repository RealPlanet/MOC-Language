#include "../include/Token.h"

void TokenList::add(Token* tok)
{
	data.push_back(tok);
}

Token* TokenList::get(int index)
{
	return data[index];
}
