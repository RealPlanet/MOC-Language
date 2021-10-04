#ifndef MOC_JMPINST_H
#define MOC_JMPINST_H
//Includes OK
#include "../BaseClasses/Instruction/Instruction.h"
#include "../Processors/Runtime/Runtime.h"
#include "../Processors/Compiler/Compiler.h"

class JmpInst : public Instruction {
public:
	JmpInst(int opcode) : Instruction(opcode) {}
	virtual int write_bytecode(Compiler& compiler, ByteBuffer* bb) const override {
		bb->write_byte8(bytecode); //Write instruction
		return 0;
	}

	virtual void execute(Runtime& rt) const override {
		rt.setIPBy(pUtil::read32(rt.getSource(), rt.getIP()));
	}
};

#endif