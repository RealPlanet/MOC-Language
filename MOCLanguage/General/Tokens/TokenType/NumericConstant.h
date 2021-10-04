#ifndef MOC_NUMERICCONST_H
#define MOC_NUMERICCONST_H
#include "..\..\BaseClasses\Writable\BCWritable.h"

/*
* Stores a number and writes it to bytecode when requested (to be expanded to support floats and other operations)
* Syntax: #N
*/
class NumericConstant : public BCWritable {
public:
	int number;
	NumericConstant(int data) : number { data } {}
	virtual int write_bytecode(Compiler& compiler, ByteBuffer* bb) const override {
		bb->write_byte32(number);
		return 0;
	}
};

#endif
