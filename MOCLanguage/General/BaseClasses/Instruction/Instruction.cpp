#include "Instruction.h"
#include "..\..\Processors\Runtime\Runtime.h"

int Instruction::write_bytecode(Compiler& compiler, ByteBuffer* bb) const{
	bb->write_byte8(bytecode);
	return 0;
}
bool Instruction::check_condition(Runtime& rt, InstCondition condition_type) const{
	switch (condition_type) {
	case InstCondition::EQUAL: {
		return rt.getMathRegister().value(Flags::ZERO) == 1;
	}
	case InstCondition::GREATER_THAN: {
		return rt.getMathRegister().value(Flags::NEGATIVE) == 0;
	}
	case InstCondition::GREATER_THAN_EQUAL: {
		return	rt.getMathRegister().value(Flags::CARRY) == 0 ||
			rt.getMathRegister().value(Flags::ZERO) == 1;
	}
	case InstCondition::LESS_THAN: {
		return	rt.getMathRegister().value(Flags::NEGATIVE) == 1;
	}
	case InstCondition::LESS_THAN_EQUAL: {
		return	rt.getMathRegister().value(Flags::CARRY) == 1 ||
			rt.getMathRegister().value(Flags::ZERO) == 1;
	}
	case InstCondition::NOT_EQUAL: {
		return rt.getMathRegister().value(Flags::ZERO) == 0;
	}
	default: return true;
	}
}
