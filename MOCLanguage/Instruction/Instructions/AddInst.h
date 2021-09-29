#include "..\Instruction.h"
#include "..\..\Runtime\Runtime.h"
#include <iostream>

class AddInst : public Instruction {
public:
	AddInst(int opcode) : Instruction(opcode) {}
	virtual void write_vm_stack(Runtime& rt, const std::vector<uint8_t>& code) const override {
		uint32_t a = rt.pop32();
		uint32_t b = rt.pop32();
		std::cout << a + b << std::endl;
		rt.push32(a+b);
	}
};