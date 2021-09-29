#pragma once
#include "Instruction.h"
class NumericConstant : public Instruction {
public:
	int number;
	NumericConstant(int data) : number { data }, Instruction(0x00) {}
	virtual void write_bytecode(ByteBuffer* bb) const override {
		bb->write_byte32(number);
	}
};