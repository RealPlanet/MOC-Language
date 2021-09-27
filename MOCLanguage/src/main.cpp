#include <iostream>

// Own code
#include "../include/util.h"
#include "../include/parser.h"
#include "../include/token.h"
// lmoc compile file.lmoc

int main(int argc, char** argv){
    if(argc < 3){
        printf("Too few arguments\n");
        return 1;
    }

    Parser parser;

    if(strcmp(argv[1], "compile") == 0){
        char* source = pUtil::read_ascii_file(argv[2]);
        TokenList tokens;
        parser.start(&tokens, source);

        // delete tokens;
        delete source;
    }

    return 0;
}