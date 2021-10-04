#ifndef MOC_BCWRITABLE_H
#define MOC_BCWRITABLE_H
// Includes OK
#include "../../Processors/Compiler/BB/Bytebuffer.h"
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
	// A const tokenlist is passed by ptr for writables to gather requried data (for example mov needs to check if the following tokens are a register and a number)
	// Returns status, if != 0 then something went wrong
	virtual int write_bytecode(Compiler& compiler, ByteBuffer* bb) const { return 0; };
};
typedef std::shared_ptr<BCWritable> BCWritablePtr;
#endif
