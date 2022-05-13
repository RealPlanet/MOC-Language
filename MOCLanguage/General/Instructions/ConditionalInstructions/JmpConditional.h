#pragma once
#include "..\JmpInst.h"
#include "../../Util.h"

class JmpConditional : public JmpInst {
	InstCondition condition_type;
public:
	JmpConditional(int opcode, InstCondition cd = InstCondition::NONE) : JmpInst(opcode), condition_type{ cd } {}
	virtual int write_bytecode(Compiler& compiler, ByteBuffer* bb) const override {
		bb->write_byte8(bytecode);
		bb->write_byte8((int)condition_type);
		return JmpInst::write_bytecode(compiler, bb);
	}

	virtual void execute(Runtime& rt) const override {
		InstCondition condition = (InstCondition)pUtil::read8(rt.getSource(), rt.getIP());
		rt.incrementIPBy(1);
		if (pUtil::check_condition(rt, condition))
			JmpInst::execute(rt);
	}
};