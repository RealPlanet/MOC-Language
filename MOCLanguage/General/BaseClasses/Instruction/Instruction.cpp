#include "Instruction.h"

int Instruction::write_bytecode(ByteBuffer* bb, const TokenList* tokens, const int i) const{
	bb->write_byte8(bytecode);
	return 0;
}
