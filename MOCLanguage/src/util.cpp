#include "../include/util.h"

void pUtil::read_ascii_file(const char* path, std::string& out_source){
    // Open file as read only
    std::ifstream file_stream(path, std::ifstream::binary);
    //FILE* file = fopen(path, "r");

    if(!file_stream.is_open()){
        printf("Could not open file '%s'\n", path);
        out_source = "";
        return;
    }
    // Return contents
    out_source.assign((std::istreambuf_iterator<char>(file_stream)),
        (std::istreambuf_iterator<char>()));
    file_stream.close();
}

std::streamoff pUtil::get_file_size(std::ifstream* stream)
{
    std::streampos fsize = stream->tellg();
    stream->seekg(0, stream->end);
    fsize = stream->tellg() - fsize;

    //Reset stream state and go back to start of file
    stream->clear();
    stream->seekg(0, stream->beg);
    return (fsize);
}