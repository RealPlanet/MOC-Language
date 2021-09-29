#pragma once
#include "..\Instruction.h"

/*
*  NUMERIC CONSTANT IS JUST A WRAPPER TO PASS NUMBERS AS FAKE INSTRUCTIONS IN THE PARSER
*  ALL INSTRUCTIONS THAT REQUIRES NUMBERS (IE PUSH) WILL HANDLE READING THE BYTECODE AND INCREMENTING THE INSTRUCTION POINTER
*/
class NumericConstant : public Instruction {
public:
	int number;
	NumericConstant(int data) : number { data }, Instruction(0x00) {}
	virtual void write_bytecode(ByteBuffer* bb) const override {
		bb->write_byte32(number);
	}
};
