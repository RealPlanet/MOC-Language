#pragma once
#include "..\Compiler\Bytebuffer.h"
#include <map>
#include <memory>

class Instruction
{
public:
	int bytecode = 0x00;

	virtual void pre_write_bytecode(ByteBuffer* bb) const {}
	virtual void post_write_bytecode(ByteBuffer* bb) const {}

	virtual void write_bytecode(ByteBuffer* bb) const {
		bb->write_byte8(bytecode);
	}

	Instruction(int bc) : bytecode{ bc } {}
};

typedef std::shared_ptr<Instruction> InstructionPtr;