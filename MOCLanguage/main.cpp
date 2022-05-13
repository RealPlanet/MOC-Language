#include <iostream>
#include <chrono>

// Own code
#include "General/util.h"
#include "General/Tokens/TokenList.h"

#include "General/Processors/Lexer/Lexer.h"
#include "General/Processors/Compiler/compiler.h"
#include "General/Processors/Runtime/Runtime.h"

#include "General/Processors/Sets/LabelTable.h"

int compile_cmd_response(int argc, char** argv);
int run_cmd_response(int argc, char** argv);

/*
*   ASSUMES BIG ENDIAN
*   <3 kappa
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
    
    std::cout << "Program has reached end of main with exit code: "<< result_code << "." << std::endl;
    return 0;
}

//Compiles given file. reports errors, and outputs to Output folder.
int compile_cmd_response(int argc, char** argv) {
    auto start = std::chrono::high_resolution_clock::now();

    std::string source = "";
    pUtil::read_ascii_file(argv[2], source);
    if (source.compare("") == 0) {
        std::cerr << "Given file was empty or could not be read!" << std::endl;
        return -1;
    }
    //Parser parser;
    
	
    TokenList tokens;
    Lexer current_lexer(tokens, source);
    current_lexer.start();
	
    if (current_lexer.get_status() != LexerStatus::SUCCESS)
        return -(int)LexerStatus::ERROR;

    Compiler compiler;
    if (compiler.start(tokens) != CompilerStatus::SUCCESS)
        return (int)CompilerStatus::ERROR;

    ByteBuffer* bytebuffer = compiler.getByteBuffer();
    Labels::LabelTable* table = compiler.getLabels();

    pUtil::create_folder("Output", ".\\");
    pUtil::write_binary_file("Output\\out.smoc", *bytebuffer);
    //table->write_labels_to_file("Output\\label_table.dmoc");

    delete bytebuffer;
    delete table;
    // Finished compiling

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds> (stop - start);
    std::cout << "Bytecode compilation completed succesfully in: " << duration.count() << " milliseconds." << std::endl;
    return (int)CompilerStatus::SUCCESS;
}

// Executes given bytecode and, if needed, outputs to console
int run_cmd_response(int argc, char** argv) {
    std::cout << "Executing given bytecode file." << std::endl;

    //I prefer to work with strings
    std::string path = pUtil::get_string_from_char(argv[2]);
    Runtime rt;
    return (int)rt.start(path);
}