#include <iostream>
#include <chrono>

// Own code
#include "General/util.h"
#include "General/Tokens/TokenList/token.h"
#include "General/Instructions/Instructionset/Instructionset.h"

#include "General/Processors/Parser/Parser.h"
#include "General/Processors/Compiler/compiler.h"
#include "General/Processors/Runtime/Runtime.h"

// lmoc compile file.lmoc
int compile_cmd_response(int argc, char** argv);
int run_cmd_response(int argc, char** argv);

/*
* 
* ASSUMES BIG ENDIAN;
* 
* 
* 
* 
*/

int main(int argc, char** argv){
    int result_code = 1;
    if(argc < 3){
        printf("Too few arguments\n");
        return result_code;
    }
     
    if(strcmp(argv[1], "compile") == 0){
        result_code = compile_cmd_response(argc, argv);
    }
    else if (strcmp(argv[1], "run") == 0) {
        result_code = run_cmd_response(argc, argv);
    }
    
    std::cout << "Program has reached end of main." << std::endl;
    return 0;
}

int compile_cmd_response(int argc, char** argv) {
    auto start = std::chrono::high_resolution_clock::now();

    std::string source = "";
    pUtil::read_ascii_file(argv[2], source);
    if (source.compare("") == 0) {
        std::cerr << "Given file was empty or could not be read!" << std::endl;
        return -1;
    }
    Parser parser;
    TokenList tokens;
    Compiler compiler;
    Instructionset is;

    if (parser.start(is, tokens, source) != ParserStatus::SUCCESS)
        return (int)ParserStatus::SYNTAX_ERROR;

    if (compiler.start(tokens) != CompilerStatus::SUCCESS)
        return (int)CompilerStatus::ERROR;

    ByteBuffer bytebuffer = compiler.getByteBuffer();
    pUtil::write_binary_file("out.stmoc", bytebuffer);
    // Finished compiling

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds> (stop - start);
    std::cout << "Bytecode compilation completed succesfully in: " << duration.count() << " milliseconds." << std::endl;
    return (int)CompilerStatus::SUCCESS;
}

int run_cmd_response(int argc, char** argv) {
    std::cout << "Executing given bytecode file." << std::endl;

    std::vector<uint8_t> code;
    pUtil::read_binary_file(argv[2], code);

    Runtime rt(code);
    Instructionset is;

    if (rt.start(is) != RuntimeStatus::SUCCESS)
        return (int)RuntimeStatus::ERROR;

    return (int)RuntimeStatus::SUCCESS;
}