#include "..\include\compiler.h"
#include "..\include\Bytecode.h"
#include <iostream>

CompilerStatus Compiler::start(const TokenList& tok)
{
	tokens = &tok;
	bytebuffer = new ByteBuffer(1);

	int token_size = tokens->size();
	for (int i = 0; i < token_size; i++) {
		Token* t = tokens->get(i);

		if (t->type == TokenType::INST) {
			
			switch (t->data) {
				//PUSH
				case (int)TokenInst::PUSH: {
					//PUSH #N
					if (tokens->get(i + 1)->type == TokenType::NUMBER) {
						bytebuffer->write_byte8(Bytecode::PUSH_CONST);
						bytebuffer->write_byte32(tokens->get(i + 1)->data);
					}
					else {
						std::cerr << "Bad push instruction" << std::endl;
						return CompilerStatus::ERROR;
					}
					break;
				}
				// ADD
				case (int)TokenInst::ADD: {
					// Assumes data is correct -- TODO -- Fix this
					bytebuffer->write_byte8(Bytecode::ADD_STACK);
					break;
				}
				// HLT
				case (int)TokenInst::HLT: {
					bytebuffer->write_byte8(Bytecode::HLT_OP);
					break;
				}
				// This case should never be reached as the parser should error out before the compiler
				default: {
					std::cerr << "Bad token instruction" << std::endl;
					return CompilerStatus::ERROR;
				}	
			}
		}
	}

	return CompilerStatus::SUCCESS;
}