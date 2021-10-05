#ifndef MOC_PRINTI_H
#define MOC_PRINTI_H
//Includes OK
#include "../BaseClasses/Instruction/Instruction.h"

/*
* Print's a numeric constant to the console
* Syntax: HLT
*/
class PrintIInst : public Instruction {
public:
	PrintIInst(int opcode) : Instruction(opcode) {}
	virtual void execute(Runtime& rt) const override {
		std::cout << pUtil::read32(rt.getSource(), rt.getIP()) << std::endl;
		rt.incrementIPBy(4);
	}
};

#endif