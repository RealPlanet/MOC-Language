#ifndef MOC_PARSER_H
#define MOC_PARSER_H
#include "Token.h"
#include "../Instruction/Instructionset.h"

#include <stdint.h>
#include <string>

enum class _ParserStatus {
	SUCCESS,
	SYNTAX_ERROR
};

typedef enum _ParserStatus ParserStatus;

class Parser{
public:
	ParserStatus start(const Instructionset& is, TokenList& list, const std::string& source);
	uint32_t get_number(const std::string& buf) const;
	const Instruction* get_inst(const Instructionset& is, const std::string& opname) const;
};

#endif // MOC_PARSER_H