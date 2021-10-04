#include "Parser.h"
#include <sstream>
#include <iostream>


#include "../../Tokens/TokenList/Token.h"
#include "../../Tokens/TokenType/NumericConstant.h"
#include "../../Tokens/TokenType/Register.h"
#include "../../Tokens/TokenType/LabelName.h"
#include "../../Processors/Sets/Instructionset.h"
#include "../../Processors/Sets/RegisterManager.h"
#include "../../Util.h"

ParserStatus Parser::start(TokenList& list, const std::string& source) {
	int line = 1;
	std::istringstream source_stream(source);
	Instructionset is;
	RegisterManager regManager;

	/*
	* For each line parse each word
	*/
	while (!source_stream.eof())
	{
		std::string next_line;
		std::getline(source_stream, next_line);
		std::istringstream line_stream(next_line);

		while (!line_stream.eof())
		{
			std::string lex;
			line_stream >> lex;
			// Sometimes an empty sting can be caught by >> so we skip it
			if (lex.compare("") == 0)
				continue;

			//This is a numerical constant
			if (lex[0] == '#') {
				int num = pUtil::get_number32(lex);
				BCWritablePtr nc = std::make_shared<NumericConstant>(num);
				list.add(Token(TokenType::NUMBER, nc, line));
			}
			else if (lex[0] == '%') {
				std::string reg_name = lex.substr(1, lex.size());
				RegisterPtr reg = regManager.get_reg(reg_name);
				if (reg != nullptr) {
					list.add(Token(TokenType::REGISTER, reg, line));
				}
				else {
					std::cout << "Syntax error: Invalid register name (" << lex << " ) at line : " << line << std::endl;
					return ParserStatus::SYNTAX_ERROR;
				}
			}
			// Must be a label OR Must be a label reference
			else if (lex[lex.size() - 1] == ':' || lex[0] == '@') {
				//For substring removal of :
				int start = 0;
				int end = lex.size() - 1;

				bool isDefinition = lex[lex.size() - 1] == ':';
				if (!isDefinition) {
					//For substring removal of @
					start = 1;
					end = lex.size();
				}
				list.add(Token(TokenType::LABEL, std::make_shared<LabelName>(lex.substr(start, end), isDefinition), line));
			}
			// Must be an instruction
			else {
				InstructionPtr instruction = is.get_instruction(lex);

				// This is "ugly" but if I ever changed the nop opcode at least I won't break the check
				if (instruction->bytecode != is.get_instruction("nop")->bytecode) {
					list.add(Token(TokenType::INST, instruction, line));
				}
				else {
					std::cout << "Syntax error: Invalid instruction (" << lex << " ) at line : " << line << std::endl;
					return ParserStatus::SYNTAX_ERROR;
				}
			}
		}

		//Every time we leave the above loop a line has been completely parsed!
		line++;
	}
	return ParserStatus::SUCCESS;
}
