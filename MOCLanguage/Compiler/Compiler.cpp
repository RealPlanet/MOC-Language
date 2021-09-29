#include "..\Compiler\compiler.h"
#include <iostream>

CompilerStatus Compiler::start(const TokenList& tok)
{
	tokens = &tok;
	bytebuffer = new ByteBuffer(1);

	int token_size = tokens->size();
	for (int i = 0; i < token_size; i++) {
		TokenPtr tok = tokens->get(i);
		//tok->inst->pre_write_bytecode(bytebuffer);
		tok->inst->write_bytecode(bytebuffer);
		//tok->inst->post_write_bytecode(bytebuffer);
	}

	return CompilerStatus::SUCCESS;
}