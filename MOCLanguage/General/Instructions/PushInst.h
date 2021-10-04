#ifndef MOC_PUSHINST_H
#define MOC_PUSHINST_H
//Includes OK
#include "../BaseClasses/Instruction/Instruction.h"
#include "../Processors/Runtime/Runtime.h"
#include "../Util.h"

class PushInst : public Instruction {
public:
	PushInst(int opcode) : Instruction(opcode) {}
	virtual void execute(Runtime& rt) const override {
		rt.push32(pUtil::read32(rt.getSource(), rt.getIP()));
		rt.incrementIPBy(4);
	}
};

#endif