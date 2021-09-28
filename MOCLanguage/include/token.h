#ifndef MOC_TOKEN_H
#define MOC_TOKEN_H

#include <vector>

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
    int data;
    int line;

    _Token(TokenType _type, int _data, int _line) : type{ _type }, data{ _data }, line{_line} {}
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