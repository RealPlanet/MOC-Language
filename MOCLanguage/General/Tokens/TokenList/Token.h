#ifndef MOC_TOKEN_H
#define MOC_TOKEN_H
#include "../../BaseClasses/Writable/BCWritable.h"

enum class _TokenType {
    INST = 0,
    NUMBER = 1
};

enum class _TokenInst {
    PUSH = 1,
    ADD = 2,
    HLT = 3
};

typedef enum _TokenInst TokenInst;
typedef enum _TokenType TokenType;

struct _Token{
    TokenType type;
    // This is only a ptr to the instruction set object, token wont handle deleting this!
    // Could be a union between InstructionPtr and number wrapper (for int/float/ecc) to avoid having to use an Instruction for numeric constants?
    const BCWritablePtr writable;
    int line;
    _Token(TokenType _type, const BCWritablePtr _write, int _line) : type{ _type }, writable{ _write }, line{ _line } {}
};

typedef struct _Token Token;

class TokenList {
    std::vector<Token> data;
public:
    void add(Token tok);
    Token get(const int index) const;

    inline size_t size() const { return data.size(); }
};

#endif // MOC_TOKEN_H