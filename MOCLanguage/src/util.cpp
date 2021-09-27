#include "../include/util.h"

char* pUtil::read_ascii_file(const char* path){
    // Open file as read only
    std::ifstream file_stream(path, std::ifstream::binary);
    //FILE* file = fopen(path, "r");

    if(!file_stream.is_open()){
        printf("Could not open file '%s'\n", path);
        return nullptr; // TODO :: This will break things if not handled properly
    }

    std::streamoff size = get_file_size(&file_stream);

    // Transfer ownership of memory to the caller
    char* buf = new char[size+1];
    if(!buf){
        printf("Could not allocate memory for file!\n");
        return nullptr; // TODO :: This will break things if not handled properly
    }

    file_stream.read(buf, size);
    buf[size] = '\0'; // Need to know when text is done being parsed
    file_stream.close();

    // Return contents
    return buf;
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