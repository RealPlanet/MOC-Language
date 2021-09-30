#include "..\Compiler\compiler.h"

CompilerStatus Compiler::start(const TokenList& tok)
{
	tokens = &tok;
	bytebuffer = new ByteBuffer(1);

	int token_size = tokens->size();

	// Convert tokens into bytecode
	for (int i = 0; i < token_size; i++) {
		Token tok = tokens->get(i);
		tok.writable->write_bytecode(bytebuffer);
	}

	return CompilerStatus::SUCCESS;
}