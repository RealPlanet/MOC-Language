#include "util.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include "Processors/Runtime/Runtime.h"


bool pUtil::take_word(const std::string& str, int start, std::string& output)
{
    int end = start;
    bool _is_whitespace = false, _is_newline = false;
    for (;  end < str.size() &&
            !(_is_whitespace = is_whitespace(str[end])) &&
            !(_is_newline = is_crlf(str[end], str[end + 1]) || is_newline(str[end]));
        end++);
	
	output = str.substr(start, end - start);
	
    return _is_newline;
}

// INSTRUCTION OPERATIONS
bool pUtil::check_condition(Runtime& rt, InstCondition condition_type)
{
    switch (condition_type) {
    case InstCondition::EQUAL: {
        return	rt.getMathRegister().value(Flags::ZERO) == 1;
    }
    case InstCondition::GREATER_THAN: {
        return	rt.getMathRegister().value(Flags::NEGATIVE) == 0;
    }
    case InstCondition::GREATER_THAN_EQUAL: {
        return	rt.getMathRegister().value(Flags::CARRY) == 0 ||
            rt.getMathRegister().value(Flags::ZERO) == 1;
    }
    case InstCondition::LESS_THAN: {
        return	rt.getMathRegister().value(Flags::NEGATIVE) == 1;
    }
    case InstCondition::LESS_THAN_EQUAL: {
        return	rt.getMathRegister().value(Flags::CARRY) == 1 ||
            rt.getMathRegister().value(Flags::ZERO) == 1;
    }
    case InstCondition::NOT_EQUAL: {
        return	rt.getMathRegister().value(Flags::ZERO) == 0;
    }
    default: return true;
    }
}

// FILE OPERATIONS
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

std::string pUtil::get_file_path(const std::string& path) {
    auto pathEnd = path.find_last_of("/\\");
    auto pathName = pathEnd == std::string::npos ? path : path.substr(0, pathEnd);
    return pathName;
}

std::string pUtil::get_file_path(const char* path)
{
    return get_file_path(get_string_from_char(path));
}

bool pUtil::create_folder(std::string name, std::string path)
{
    return std::filesystem::create_directory(path + "\\" + name);
}

// NUMBER OPERATIONS
uint32_t pUtil::get_number32(const std::string& buf) {
    std::string str = buf.substr(1, buf.size());
    long num = std::stoi(str);

    // By choice numbers are 32 bit.
    return (num <= UINT32_MAX) ? num : 0;
}

int pUtil::get_number(const std::string& buf) {
    return std::stoi(buf);
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

// STRING OPERATIONS
void pUtil::ltrim(std::string& s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

void pUtil::rtrim(std::string& s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

void pUtil::trim(std::string& s) {
    ltrim(s);
    rtrim(s);
}

std::string pUtil::get_string_from_char(const char* path)
{
    int arrsize = strlen(path);
    std::string s = "";
    for (int i = 0; i < arrsize; i++)
        s += path[i];
    return s;
}
