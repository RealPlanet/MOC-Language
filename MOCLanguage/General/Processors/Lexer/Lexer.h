#ifndef MOC_PARSER_H
#define MOC_PARSER_H

#include <string>
#include <sstream>
#include "../../BaseClasses/Instruction/Instruction.h"
#include "../../Processors/Sets/Instructionset.h"
#include "../../Processors/Sets/RegisterManager.h"
#include "../../Tokens/TokenList.h"

class InstructionSet;
class RegisterManager;
class TokenList;

enum class _LexerStatus {
	SUCCESS,
	ERROR
};
typedef enum _LexerStatus LexerStatus;

class Lexer{
public:
	Lexer(TokenList& token_list, const std::string& source_text) : tokens{ token_list }, source{ source_text }{
	}
	
	void start();
	inline LexerStatus get_status(){ return status; }
private:
	void parse_label_token();
	void parse_register_token();
	void parse_literal_token();
	void parse_instruction_token();
	void parse_string_token();
	void parse_number_token();

	TokenList& tokens;
	//std::istringstream source_stream;
	//std::istringstream line_stream;
	const std::string& source;
	//std::string current_line;
	std::string current_lex;
	int	current_line_number;
	int current_char_index;

	LexerStatus status = LexerStatus::SUCCESS;
	InstructionSet instruction_set;
	RegisterManager register_manager;
};

#endif // MOC_PARSER_H