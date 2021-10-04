#ifndef MOC_BCWRITABLE_H
#define MOC_BCWRITABLE_H
// Includes OK
#include "../../Processors/Compiler/Bytebuffer.h"
#include <memory>

/*
* Base class for any object which needs to write bytecode data
*/
class TokenList;
class Compiler;
class BCWritable {
public:
	// Most instructions will only need this, but it could be overwritten if needed (Runtime needs to be able to know the size of the instruction)
	// Bytebuffer is passed for writing
	// 
	// A const tokenlist is passed by ptr for writables to gather requried data (for example mov needs to check if the following are both registers
	// or first is a register and second is a number)
	// i is the position in the tokenlist of this token
	// Returns status, if != 0 then something went wrong
	virtual int write_bytecode(Compiler& compiler, ByteBuffer* bb) const { return 0; };
};
typedef std::shared_ptr<BCWritable> BCWritablePtr;
#endif
