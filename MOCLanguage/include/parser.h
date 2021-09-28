#ifndef MOC_PARSER_H
#define MOC_PARSER_H
#include "../include/Token.h"
#include <stdint.h>
#include <string>
#include <limits>

enum class _ParserStatus {
	SUCCESS,
	SYNTAX_ERROR
};

typedef enum _ParserStatus ParserStatus;

class Parser{
public:
	ParserStatus start(TokenList* list, const std::string& source);
	uint32_t get_number(const std::string& buf) const;
	TokenInst get_inst(const std::string& buf) const;
private:
};

#endif // MOC_PARSER_H