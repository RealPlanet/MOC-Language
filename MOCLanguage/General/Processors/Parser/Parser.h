#ifndef MOC_PARSER_H
#define MOC_PARSER_H
#include <string>
#include "../../BaseClasses/Instruction/Instruction.h"

class Instructionset;
class TokenList;
enum class _ParserStatus {
	SUCCESS,
	SYNTAX_ERROR
};

typedef enum _ParserStatus ParserStatus;

class Parser{
public:
	ParserStatus start(const Instructionset& is, TokenList& list, const std::string& source);
	uint32_t get_number(const std::string& buf) const;
	InstructionPtr get_inst(const Instructionset& is, const std::string& opname) const;
};

#endif // MOC_PARSER_H