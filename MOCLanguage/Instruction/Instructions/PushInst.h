#pragma once
#include "..\Instruction.h"
#include "..\..\Runtime\Runtime.h"
#include <iostream>

class PushInst : public Instruction {
public:
	PushInst(int opcode) : Instruction(opcode) {}
	virtual void write_vm_stack(Runtime& rt, const std::vector<uint8_t>& code) const override {
		rt.push32(pUtil::read32(code, rt.getIP()));
		rt.incrementIPBy(4);
	}
};