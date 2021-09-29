#pragma once
#include "Instruction.h"
class NumericConstant : public Instruction {
public:
	int number;
	NumericConstant(int data) : number { data }, Instruction(0x00) {}
	virtual void write_bytecode(ByteBuffer* bb) const override {
		std::cout << "Writing 32" << std::endl;
		bb->write_byte32(number);
	}
};