#ifndef MOC_TOKEN_H
#define MOC_TOKEN_H

#include <vector>

enum class _TokenType {
    INST,
    NUMBER
};

enum class _TokenInst {
    PUSH,
    ADD,
    HLT
};
typedef enum _TokenInst TokenInst;
typedef enum _TokenType TokenType;

struct _Token{
    int type;
    int data;
    int line;

    _Token(int _type, int _data, int _line) : type{ _type }, data{ _data }, line{_line} {}
};

typedef struct _Token Token;

class TokenList {
    std::vector<Token*> data;

    //TokenList* token_list_create(int size);
    //void token_list_destroy(TokenList* list);
public:
    void add(Token* tok);
    Token* get(int index);
    inline int size() { return data.size(); }
};

#endif // MOC_TOKEN_H