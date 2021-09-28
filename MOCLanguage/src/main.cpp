#include <iostream>

// Own code
#include "../include/util.h"
#include "../include/parser.h"
#include "../include/token.h"
#include "../include/compiler.h"
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
        Compiler compiler;

        if (parser.start(&tokens, source) != ParserStatus::SUCCESS)
            return 1;

        if (compiler.start(tokens) != CompilerStatus::SUCCESS)
            return 1;

        ByteBuffer bytebuffer = compiler.getByteBuffer();
        pUtil::write_binary_file("out.stmoc", bytebuffer);
    }

    return 0;
}