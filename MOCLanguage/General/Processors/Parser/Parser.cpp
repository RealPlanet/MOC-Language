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
#include "../../Tokens/TokenType/StringConstant.h"

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
		int line_index = 0; //Added for string support

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
			// This is a string constant
			else if(lex[0] == '\"') { // TODO :: THIS IS BAD, POSSIBLY REWORK, CURRENTLY DOESNT WORK!
				// Look for corresponding " on this line
				int literal_size = 0;
				int string_offset = 3; //Magic Number :: Stream skips whitespace and " before string
				for (int i = 0; i < next_line.size(); i++) {
					literal_size++;
					int index = line_index + string_offset + i;
					char c = next_line[index];
					if ( c == '\"')
						break;
				}

				std::string literal_string = next_line.substr(line_index + string_offset, line_index + literal_size);
				pUtil::trim(literal_string);
				BCWritablePtr sc = std::make_shared<StringConstant>(literal_string);
				//list.add(Token(TokenType::STRING, sc, line));
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

			line_index += lex.size();
		}

		//Every time we leave the above loop a line has been completely parsed!
		line++;
	}
	return ParserStatus::SUCCESS;
}
