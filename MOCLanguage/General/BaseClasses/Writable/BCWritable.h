#ifndef MOC_BCWRITABLE_H
#define MOC_BCWRITABLE_H
// Includes OK
#include "../../Processors/Compiler/Bytebuffer.h"
#include <memory>

/*
* Base class for any object which needs to write bytecode data
*/
class BCWritable {
public:
	virtual void write_bytecode(ByteBuffer* bb) const {};
};
typedef std::shared_ptr<BCWritable> BCWritablePtr;
#endif
