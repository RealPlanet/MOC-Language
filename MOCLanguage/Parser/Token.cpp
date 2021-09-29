#include "Token.h"

void TokenList::add(TokenPtr tok)
{
	data.push_back(tok);
}

TokenPtr TokenList::get(const int index) const
{
	return data[index];
}
