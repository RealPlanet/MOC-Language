#ifndef MOC_TOKEN_H
#define MOC_TOKEN_H

struct _Token{
    int type;
    int data;
    int line;
};

typedef struct _Token Token;

Token* create_token(int data, int type, int line);
void destroy_token(Token* tok);

typedef struct _TokenList TokenList;

class TokenList {
    Token** data;
    int ptr;
    int size;

    //TokenList* token_list_create(int size);
    //void token_list_destroy(TokenList* list);
    void token_list_add();
    Token* token_list_get(TokenList* list, int index);
};

#endif // MOC_TOKEN_H