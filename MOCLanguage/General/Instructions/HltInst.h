#ifndef MOC_HLTINST_H
#define MOC_HLTINST_H
//Includes OK
#include "../BaseClasses/Instruction/Instruction.h"
#include "../Processors/Runtime/Runtime.h"

/*
* If a number is available at the top of the stack it's used as exit code.
* Syntax: HLT
*/
class HltInst : public Instruction {
public:
	HltInst(int opcode) : Instruction(opcode) {}
	virtual void execute(Runtime& rt) const override {

		if(rt.stackSize() > 0)
			rt.setExitCode(rt.pop8());
		else
			rt.setExitCode(0);
		rt.setRunningStatus(false);
	}
};

#endif