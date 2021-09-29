#ifndef MOC_COMPILER_H
#define MOC_COMPILER_H
#include "..\Parser\Token.h"
#include "Bytebuffer.h"


#define STACK_SIZE 1024
enum class _CompilerStatus {
	SUCCESS,
	ERROR
};

typedef enum _CompilerStatus CompilerStatus;

class Compiler {
private:
	// Contains last registered status
	CompilerStatus status;
	const TokenList* tokens;
	ByteBuffer* bytebuffer;
	

public:
	CompilerStatus start(const TokenList& tok);
	inline ByteBuffer getByteBuffer() { return *bytebuffer; }
};

#endif
