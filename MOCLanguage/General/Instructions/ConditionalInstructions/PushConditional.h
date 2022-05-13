#include "..\PushInst.h"

class PushConditional : public PushInst {
	InstCondition condition_type;
public:
	PushConditional(int opcode, InstCondition cd = InstCondition::NONE) : PushInst(opcode), condition_type{cd} {}
	virtual int write_bytecode(Compiler& compiler, ByteBuffer* bb) const override {
		bb->write_byte8(bytecode);
		bb->write_byte8((int)condition_type);
		return PushInst::write_push_data(compiler, bb);
	}

	virtual void execute(Runtime& rt) const override {
		InstCondition condition = (InstCondition)pUtil::read8(rt.getSource(), rt.getIP());
		rt.incrementIPBy(1);
		if (pUtil::check_condition(rt, condition))
			PushInst::execute(rt);
	}
};