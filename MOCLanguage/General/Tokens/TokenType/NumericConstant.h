#ifndef MOC_NUMERICCONST_H
#define MOC_NUMERICCONST_H
#include "..\..\BaseClasses\Writable\BCWritable.h"

class NumericConstant : public BCWritable {
public:
	int number;
	NumericConstant(int data) : number { data } {}
	virtual int write_bytecode(ByteBuffer* bb, const TokenList* tokens, const int i) const override {
		bb->write_byte32(number);
		return 0;
	}
};

#endif
