#ifndef MOC_STRINGCONST_H
#define MOC_STRINGCONST_H
#include "..\..\BaseClasses\Writable\BCWritable.h"

/*
* Stores a string and writes it to bytecode when requested
* Syntax: "TEXT"
*/
class StringConstant : public BCWritable {
public:
	std::string data;
	StringConstant(std::string data) : data{ data } {}
	virtual int write_bytecode(Compiler& compiler, ByteBuffer* bb) const override {
		int string_size = data.size();
		bb->write_byte32(string_size);
		for (int i = 0; i < string_size; i++)
			bb->write_byte8(data[i]);

		return 0;
	}
};

#endif