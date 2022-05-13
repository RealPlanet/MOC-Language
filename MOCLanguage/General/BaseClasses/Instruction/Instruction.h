#ifndef MOC_INST_H
#define MOC_INST_H
// Includes OK
#include<vector>
#include "..\Writable\BCWritable.h"
#include "..\..\Processors\Compiler\BB\Bytebuffer.h"
#include "..\..\Processors\Runtime\MathRegister\MathRegister.h"

enum class InstCondition {
	NONE,
	EQUAL,
	NOT_EQUAL,
	GREATER_THAN,
	GREATER_THAN_EQUAL,
	LESS_THAN,
	LESS_THAN_EQUAL
};

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