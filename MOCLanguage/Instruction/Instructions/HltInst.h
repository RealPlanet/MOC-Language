#pragma once
#include "..\Instruction.h"
#include "..\..\Runtime\Runtime.h"

class HltInst : public Instruction {
public:
	HltInst(int opcode) : Instruction(opcode) {}
	virtual void write_vm_stack(Runtime& rt, const std::vector<uint8_t>& code) const override {
		rt.setExitCode(rt.pop8());
		rt.setRunningStatus(false);
	}
};