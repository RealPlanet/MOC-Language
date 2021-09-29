#ifndef MOC_TOKEN_H
#define MOC_TOKEN_H

#include <vector>
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
    const Instruction* inst;
    int line;
    _Token(TokenType _type, const Instruction* _inst, int _line) : type{ _type }, inst{ _inst }, line{ _line } {}

    ~_Token() {
        //delete inst;
    }
};

typedef struct _Token Token;

class TokenList {
    std::vector<Token*> data;
public:
    ~TokenList() {
        for (auto val : data) {
            delete val;
        }
    }
public:
    void add(Token* tok);
    Token* get(const int index) const;
    inline int size() const { return data.size(); }
};

#endif // MOC_TOKEN_H