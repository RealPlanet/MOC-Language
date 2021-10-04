#ifndef MOC_SUBINST_H
#define MOC_SUBINST_H
//Includes OK
#include "../BaseClasses/Instruction/Instruction.h"
#include "../Processors/Runtime/Runtime.h"
#include<iostream>
class SubInst : public Instruction {
public:
	SubInst(int opcode) : Instruction(opcode) {}
	virtual void execute(Runtime& rt) const override {
		uint32_t a = rt.pop32();
		uint32_t b = rt.pop32();
		rt.push32(b - a);
		std::cout << b - a << std::endl;
	}
};

#endif //!MOC_SUBINST_H