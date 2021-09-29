#include "Instruction.h"
#include "..\Runtime\Runtime.h"

void Instruction::write_bytecode(ByteBuffer* bb) const{
	bb->write_byte8(bytecode);
}

void Instruction::write_vm_stack(Runtime& rt, const std::vector<uint8_t>& code) const
{
}