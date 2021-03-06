#ifndef MOC_REGISTER_H
#define MOC_REGISTER_H
#include "..\..\BaseClasses\Writable\BCWritable.h"
#include <memory>
/*
* Basic implementation of a register (to be expanded to support floats and other operations)
* Stores a value, bytecode in this class refers to register number
*/
class Register : public BCWritable {
public:
	int bytecode = 0x00;
	int stored_value = -1;

	Register(int reg_code) : bytecode{reg_code} {}
	virtual int write_bytecode(Compiler& compiler, ByteBuffer* bb) const override {
		bb->write_byte8(bytecode);
		return 0;
	}
};
typedef std::shared_ptr<Register> RegisterPtr;
#endif // !MOC_REGISTER_H