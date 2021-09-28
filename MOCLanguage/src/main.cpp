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
        std::string source = "";
        pUtil::read_ascii_file(argv[2], source);
        if (source.compare("") == 0) {
            std::cerr << "Given file was empty or could not be read!" << std::endl;
            return -1;
        }

        TokenList tokens;
        ParserStatus pstat = parser.start(&tokens, source);
        if (pstat != ParserStatus::SUCCESS)
            return (int)pstat;
        for (int i = 0; i < tokens.size(); i++) {
            Token* tok = tokens.get(i);
            std::cout << tok->type << "," << tok->data << "," << tok->line << std::endl;
        }
    }

    return 0;
}