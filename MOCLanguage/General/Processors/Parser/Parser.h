#ifndef MOC_PARSER_H
#define MOC_PARSER_H
#include <string>
#include "../../BaseClasses/Instruction/Instruction.h"

class Instructionset;
class RegisterManager;
class TokenList;
enum class _ParserStatus {
	SUCCESS,
	SYNTAX_ERROR
};

typedef enum _ParserStatus ParserStatus;

class Parser{
public:
	ParserStatus start( TokenList& list, const std::string& source);
};

#endif // MOC_PARSER_H