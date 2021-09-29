#include <iostream>
#include <sstream>
#include <limits>

#include "Parser.h"
#include "../Instruction/Instructions/NumericConstant.h"

ParserStatus Parser::start(const Instructionset& is, TokenList& list, const std::string& source) {
	int line = 1;
	std::istringstream source_stream(source);

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
				int num = get_number(lex);
				InstructionPtr nc = std::make_shared<NumericConstant>(num);
				list.add(Token(TokenType::NUMBER, nc, line));
			}
			// Must be an instruction
			else {
				InstructionPtr instruction = get_inst(is, lex);

				// This is "ugly" but if I ever changed the nop opcode at least I won't break the check
				if (instruction->bytecode != get_inst(is, "nop")->bytecode) {
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

uint32_t Parser::get_number(const std::string& buf) const {
	std::string str = buf.substr(1, buf.size());
	long num = std::stoi(str);

	// By choice numbers are 32 bit.
	return (num <= UINT32_MAX) ? num : 0;
}

InstructionPtr Parser::get_inst(const Instructionset& is, const std::string& opname) const {
	return is.get_instruction(opname);
}