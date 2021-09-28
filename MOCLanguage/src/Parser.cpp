#include "../include/parser.h"
#include "../include/token.h"
#include <string>
#include <iostream>
#include <sstream>

ParserStatus Parser::start(TokenList* list,const std::string& source){
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

			std::cout << lex << "Line number is: " << line << std::endl;
			//This is a numerical constant
			if (lex[0] == '#') {
				int num = get_number(lex);
				list->add(new Token((int)TokenType::NUMBER, num, line));
			}
			// Must be an instruction
			else {
				int inst = (int)get_inst(lex);
				if (inst >= 0)
					list->add(new Token((int)TokenType::INST, inst, line));
				else
				{
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
	return (num <= UINT32_MAX) ? num : 0;
}

TokenInst Parser::get_inst(const std::string& buf) const {

	if (buf.compare("push") == 0)
		return TokenInst::PUSH;
	if(buf.compare("add") == 0)
		return TokenInst::ADD;
	if (buf.compare("hlt") == 0)
		return TokenInst::HLT;

	return (TokenInst)-1;
}
