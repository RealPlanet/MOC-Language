#ifndef MOC_TOKEN_H
#define MOC_TOKEN_H
#include "../BaseClasses/Writable/BCWritable.h"
#include <vector>

// Enum to store all types of token
enum class _TokenType {
    INST = 0,
    NUMBER,
    REGISTER,
    LABEL,
	STRING
};

typedef enum _TokenType TokenType;

// Basic structure of every token parsed from the source code
struct _Token{
    TokenType type;
    const BCWritablePtr writable;
    int line;
    _Token(TokenType _type, const BCWritablePtr _write, int _line) : type{ _type }, writable{ _write }, line{ _line } {}
};
typedef struct _Token Token;

// Token list stores all tokens generated from parsing the source code and will be used to generate the bytecode on compile
class TokenList {
    std::vector<Token> data;
public:
    void add(Token tok);
    Token get(const int index) const;

    inline size_t size() const { return data.size(); }
};

#endif // MOC_TOKEN_H