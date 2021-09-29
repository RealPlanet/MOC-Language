#include "Token.h"

void TokenList::add(Token* tok)
{
	data.push_back(tok);
}

Token* TokenList::get(const int index) const
{
	return data[index];
}
