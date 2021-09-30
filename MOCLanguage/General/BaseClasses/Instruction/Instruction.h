#ifndef MOC_INST_H
#define MOC_INST_H
// Includes OK
#include<vector>
#include "..\Writable\BCWritable.h"
#include "..\..\Processors\Compiler\Bytebuffer.h"

/*
* An instruction describes how a plain text instruction (i.e "push") is converted to bytecode, generally this is enough
* But the class can be derived for custom behaviour.
* 
* Constants ALSO use this class to register themselves into the token list but won't have a valid opcode ( == NOP )
*/
class Runtime;
class Instruction : public BCWritable
{
public:
	int bytecode = 0x00;
	Instruction(int bc) : bytecode{ bc } {}
	virtual void write_vm_stack(Runtime& rt, const std::vector<uint8_t>& code) const {};

	// Inherited via BCWritable
	virtual void write_bytecode(ByteBuffer* bb) const override;
};

typedef std::shared_ptr<Instruction> InstructionPtr;

#endif