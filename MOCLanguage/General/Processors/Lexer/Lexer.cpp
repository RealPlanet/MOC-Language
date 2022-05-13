#include "Lexer.h"
#include <iostream>

#include "../../Tokens/TokenDefinition/NumericConstant.h"
#include "../../Tokens/TokenDefinition/Register.h"
#include "../../Tokens/TokenDefinition/LabelName.h"
#include "../../Tokens/TokenDefinition/StringConstant.h"


#include "../../Util.h"

void Lexer::start() {
	int current_line_number = 1;

	/*
	* For each current_line_number parse each word
	*/
	//while (!source_stream.eof() && status == LexerStatus::SUCCESS)
	for(current_char_index = 0; current_char_index < source.size() && status != LexerStatus::ERROR; current_char_index += current_lex.size())
	{
		pUtil::take_word(source, current_char_index, current_lex);
		
		// Sometimes an empty sting can be caught by >> so we skip it
		if (!current_lex.compare("") || !current_lex.compare(" ")) {
			current_char_index++;
			continue;
		}
			
			
		//This is a numerical constant
		if (current_lex[0] == '#') {
			parse_literal_token();
		}
		else if (current_lex[0] == '%') {
			parse_register_token();
		}
		else if (current_lex[current_lex.size() - 1] == ':' || current_lex[0] == '@') {
			// Must be a label OR Must be a label reference
			parse_label_token();
		}
		else {
			// Must be an instruction
			parse_instruction_token();
		}

		//Every time we leave the above loop a current_line_number has been completely parsed!
		//current_line_number++;
	}
}

void Lexer::parse_label_token()
{
	//For substring removal of :
	int start = 0;
	int end = current_lex.size() - 1;

	bool isDefinition = current_lex[current_lex.size() - 1] == ':';
	if (!isDefinition) {
		//For substring removal of @
		start = 1;
		end = current_lex.size();
	}
	tokens.add(Token(TokenType::LABEL, std::make_shared<LabelName>(current_lex.substr(start, end), isDefinition), current_line_number));
}

void Lexer::parse_register_token()
{
	std::string reg_name = current_lex.substr(1, current_lex.size());
	RegisterPtr reg = register_manager.get_reg(reg_name);
	if (reg != nullptr) {
		tokens.add(Token(TokenType::REGISTER, reg, current_line_number));
	}
	else {
		std::cout << "Syntax error: Invalid register name (" << current_lex << " ) at current_line_number : " << current_line_number << std::endl;
		this->status = LexerStatus::ERROR;
	}
}

void Lexer::parse_literal_token(){
	if (current_lex[1] == '\"') {
		parse_string_token();
		return;
	}
	
	parse_number_token();
}

void Lexer::parse_instruction_token(){
	InstructionPtr instruction = instruction_set.get_instruction(current_lex);

	// This is "ugly" but if I ever changed the nop opcode at least I won't break the check
	if (instruction->bytecode != instruction_set.get_instruction("nop")->bytecode) {
		tokens.add(Token(TokenType::INST, instruction, current_line_number));
	}
	else {
		std::cout << "Syntax error: Invalid instruction (" << current_lex << " ) at line : " << current_line_number << std::endl;
		this->status = LexerStatus::ERROR;
	}
}

void Lexer::parse_string_token() {
	int start = current_char_index + 2; // Skip # and skip \"
	int end = start;
	for (; source[end] != '\"'; end++);
	
	std::string literal_string = source.substr(start, end-start);
	current_char_index -= current_lex.size(); // Remove the lex length as this will be added back in once the main lex loop iteration finishes
	current_char_index += literal_string.size() + 3; // Accounts for begin and end quotation marks	 and #
	BCWritablePtr sc = std::make_shared<StringConstant>(literal_string);
	tokens.add(Token(TokenType::STRING, sc, current_line_number));
}

void Lexer::parse_number_token() {
	int num = pUtil::get_number32(current_lex);
	BCWritablePtr nc = std::make_shared<NumericConstant>(num);
	tokens.add(Token(TokenType::NUMBER, nc, current_line_number));
}
