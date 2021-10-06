#ifndef MOC_CMPINST_H
#define MOC_CMPINST_H
//Includes OK
#include <algorithm>
#include "../BaseClasses/Instruction/Instruction.h"
#include "../Processors/Runtime/Runtime.h"
#include "../Processors/Compiler/Compiler.h"
#include "../Util.h"
/*
*  Jumps to given label.
*
*  Syntax: JMP @<name>
*/
class CmpInst : public Instruction {
public:
	CmpInst(int opcode) : Instruction(opcode) {}
	virtual int write_bytecode(Compiler& compiler, ByteBuffer* bb) const override {
		bb->write_byte8(bytecode); //Write instruction
		return 0;
	}

	virtual void execute(Runtime& rt) const override {
		uint32_t a = pUtil::read32(rt.getSource(), rt.getIP());
		uint32_t b = pUtil::read32(rt.getSource(), rt.getIP() + 4); //Read next byte

		bool result = a - b == 0;
		
		rt.getMathRegister().update(Flags::ZERO,	(int)result);
		//Not sure on carry update
		rt.getMathRegister().update(Flags::CARRY,	(int)!result);

		rt.incrementIPBy(8);
	}
};

#endif // !MOC_CMPINST_H