#include "util.h"
#include <fstream>
#include <iostream>

void pUtil::read_ascii_file(const char* path, std::string& out_source){
    // Open file as read only
    std::ifstream file_stream(path, std::ifstream::binary);

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

void pUtil::read_binary_file(const char* path, std::vector<uint8_t>& out_code)
{
    // Open file as read only
    std::ifstream file_stream(path, std::ifstream::binary);
    if (!file_stream.is_open()) {
        printf("Could not open file '%s'\n", path);
        out_code.clear();
        return;
    }

    while (!file_stream.eof()) {
        char fileByte;
        file_stream.read(&fileByte, 1);
        out_code.push_back(fileByte);
    }

    file_stream.close();
}

void pUtil::write_binary_file(const std::string path, ByteBuffer& bb)
{
    std::ofstream output(path, std::ios::binary);
    if (!output) {
        std::cerr << "Could not write to file ( " << path << " )" << std::endl;
        return;
    }

    for (auto val : bb.buffer) {
        output << val;
    }
}

uint8_t pUtil::read8(const std::vector<uint8_t>& buffer, uint32_t index)
{
    return buffer[index];
}

uint16_t pUtil::read16(const std::vector<uint8_t>& buffer, uint32_t index)
{
    return (buffer[index] << 8) | (buffer[index + 1]);
}

uint32_t pUtil::read32(const std::vector<uint8_t>& buffer, uint32_t index)
{
    return  (buffer[index] << 24) |
            (buffer[index + 1] << 16) |
            (buffer[index + 2] << 8) |
            (buffer[index + 3]);
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

uint32_t pUtil::get_number(const std::string& buf) {
    std::string str = buf.substr(1, buf.size());
    long num = std::stoi(str);

    // By choice numbers are 32 bit.
    return (num <= UINT32_MAX) ? num : 0;
}