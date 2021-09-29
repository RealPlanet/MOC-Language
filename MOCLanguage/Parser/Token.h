#ifndef MOC_TOKEN_H
#define MOC_TOKEN_H

#include <vector>
#include <memory>
#include "..\Instruction\Instruction.h"

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
    const InstructionPtr inst;
    int line;
    _Token(TokenType _type, const InstructionPtr _inst, int _line) : type{ _type }, inst{ _inst }, line{ _line } {}
};

typedef struct _Token Token;
// TODO :: Unused? Remove
typedef std::shared_ptr<Token> TokenPtr;

class TokenList {
    std::vector<Token> data;
public:
    void add(Token tok);
    Token get(const int index) const;

    inline int size() const { return data.size(); }
};

#endif // MOC_TOKEN_H