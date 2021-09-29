#include "..\Compiler\compiler.h"
#include <iostream>

CompilerStatus Compiler::start(const TokenList& tok)
{
	tokens = &tok;
	bytebuffer = new ByteBuffer(1);

	int token_size = tokens->size();

	// Convert tokens into bytecode
	for (int i = 0; i < token_size; i++) {
		Token tok = tokens->get(i);
		/*
		* Not sure if the pre and post calls are even useful but I thought it'd be cool to have them, could be used for error checking syntax
		*/
		tok.inst->pre_write_bytecode(bytebuffer);
		tok.inst->write_bytecode(bytebuffer);
		tok.inst->post_write_bytecode(bytebuffer);
	}

	return CompilerStatus::SUCCESS;
}