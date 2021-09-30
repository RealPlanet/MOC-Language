#ifndef MOC_COMPILER_H
#define MOC_COMPILER_H
//Includes OK
#include "Bytebuffer.h"
#include "..\..\Tokens\TokenList\Token.h"

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
