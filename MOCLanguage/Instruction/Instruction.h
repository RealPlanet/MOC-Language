#pragma once
#include "..\Compiler\Bytebuffer.h"
#include <map>
#include <memory>

/*
* An instruction describes how a plain text instruction (i.e "push") is converted to bytecode, generally this is enough
* But the class can be derived for custom behaviour.
* 
* Constants ALSO use this class to register themselves into the token list but won't have a valid opcode ( == NOP )
*/

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