#ifndef MOC_MULINST_H
#define MOC_MULINST_H
//Includes OK
#include "../BaseClasses/Instruction/Instruction.h"
#include "../Processors/Runtime/Runtime.h"
#include <iostream>

class MulInst : public Instruction {
public:
	MulInst(int opcode) : Instruction(opcode) {}
	virtual void execute(Runtime& rt, const RegisterManager& regMan, const std::vector<uint8_t>& code) const override {
		uint32_t a = rt.pop32();
		uint32_t b = rt.pop32();
		rt.push32(a * b);
		std::cout << a * b << std::endl;
	}
};

#endif //!MOC_MULINST_H