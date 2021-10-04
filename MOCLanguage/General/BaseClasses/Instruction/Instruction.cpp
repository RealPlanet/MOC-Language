#include "Instruction.h"

int Instruction::write_bytecode(Compiler& compiler, ByteBuffer* bb) const{
	bb->write_byte8(bytecode);
	return 0;
}
