#pragma once
#include "..\Compiler\Bytebuffer.h"
#include <map>

class Instruction
{
public:
	int bytecode = 0x00;
	virtual void write_bytecode(ByteBuffer* bb) const {
		bb->write_byte8(bytecode);
	};

	Instruction(int bc) : bytecode{ bc } {}
};