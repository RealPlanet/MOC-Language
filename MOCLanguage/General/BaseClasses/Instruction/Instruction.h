#ifndef MOC_INST_H
#define MOC_INST_H
// Includes OK
#include<vector>
#include "..\Writable\BCWritable.h"
#include "..\..\Processors\Compiler\BB\Bytebuffer.h"

/*
* An instruction describes how a plain text instruction (i.e "push") is converted to bytecode, generally this is enough
* But the class can be derived for custom behaviour (Example : ).
* 
*/
class Runtime;
class RegisterManager;
class Instruction : public BCWritable
{
public:
	int bytecode = 0x00;

	Instruction(int bc) : bytecode{ bc } {}
	virtual void execute(Runtime& rt) const {};

	// Inherited via BCWritable
	virtual int write_bytecode(Compiler& compiler, ByteBuffer* bb) const override;
};

// Simplification for shared_ptr defitinion
typedef std::shared_ptr<Instruction> InstructionPtr;

#endif