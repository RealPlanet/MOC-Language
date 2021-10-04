#ifndef MOC_COMPILER_H
#define MOC_COMPILER_H
//Includes OK
#include "BB/Bytebuffer.h"
#include "../../Tokens/TokenList/Token.h"
#include "../Sets/LabelTable.h"

enum class _CompilerStatus {
	SUCCESS,
	ERROR
};

typedef enum _CompilerStatus CompilerStatus;

class Compiler {
private:
	const TokenList* tokens = nullptr;
	ByteBuffer* bytebuffer = nullptr;
	Labels::LabelTable* label_table = nullptr;

	//Stores all JMP instructions to check at the end of compile. If some have unresolved jump an error is thrown.
	std::vector<Labels::LabelInfo> missingLabels;

	int token_index = 0;
public:
	CompilerStatus start(const TokenList& tok);
	inline ByteBuffer* getByteBuffer() { return bytebuffer; }
	inline int getTokenIndex() const { return token_index; }
	inline const TokenList* getTokenList() { return tokens; }
	inline Labels::LabelTable* getLabels() { return label_table; }
	inline std::vector<Labels::LabelInfo>& getUndefinedLabelReferences() { return missingLabels; }
};

#endif
