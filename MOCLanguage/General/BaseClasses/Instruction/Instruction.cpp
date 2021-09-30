#include "Instruction.h"

void Instruction::write_bytecode(ByteBuffer* bb) const{
	bb->write_byte8(bytecode);
}
