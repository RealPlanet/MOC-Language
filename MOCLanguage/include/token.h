#ifndef MOC_TOKEN_H
#define MOC_TOKEN_H

struct _Token{
    int data;
    int type;
    int line;
};

typedef struct _Token Token;

Token* create_token(int data, int type, int line);
void destroy_token(Token* tok);

struct _TokenList{
    Token** data;
    int ptr;
    int size;
};
typedef struct _TokenList TokenList;

TokenList* create_token_list(int size);
void token_list_add();
void token_list_destroy(TokenList* list);

#endif // MOC_TOKEN_H