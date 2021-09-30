#ifndef MOC_ADDINST_H
#define MOC_ADDINST_H
//Includes OK
#include "../BaseClasses/Instruction/Instruction.h"
#include "../Processors/Runtime/Runtime.h"

class AddInst : public Instruction {
public:
	AddInst(int opcode) : Instruction(opcode) {}
	virtual void write_vm_stack(Runtime& rt, const std::vector<uint8_t>& code) const override {
		uint32_t a = rt.pop32();
		uint32_t b = rt.pop32();
		rt.push32(a+b);
	}
};

#endif