#ifndef MOC_UTIL_H
#define MOC_UTIL_H
//Includes OK
#include <vector>
#include <string>
#include "Processors/Compiler/BB/Bytebuffer.h"

enum class InstCondition;
class Runtime;
namespace pUtil {
	inline bool is_crlf(const char c1, const char c2) {
		return c1 == '\r' && c2 == '\n';
	}
	inline bool is_whitespace(const char c){
		return c == ' ';
	}
	inline bool is_newline(const char c){
		return c == '\n' || c == '\r' || c == '\t';
	}
	void take_word(const std::string& str, int start, std::string& output);
		
	// INSTRUCTION OPERATIONS
	bool check_condition(Runtime& rt, InstCondition condition_type);
	// FILE OPERATIONS
	// Read file in text mode, save entire contents in a single string (out_source)
	void read_ascii_file(const char* path, std::string& out_source);
	//Read file in binary mode and write its contents in a vector, each element in the vector is one byte of the file contents
	void read_binary_file(const char* path, std::vector<uint8_t>& out_code);
	//Write bytebuffer to a text file in binary format
	void write_binary_file(std::string path, ByteBuffer& bb);
	//Gets file size by seeking
	std::streamoff get_file_size(std::ifstream* stream);
	// Returns file path without the file name included
	std::string get_file_path(const std::string& path);
	std::string get_file_path(const char* path);
	//Create folder at path
	bool create_folder(std::string name, std::string path);

	// NUMBER OPERATIONS
	//Converts numeric constant (#N) to number (also handles removing # from string)
	uint32_t get_number32(const std::string& buf);
	//Converts string to int
	int get_number(const std::string& buf);
	// Read 8/16/32 bits from a buffer at index
	uint8_t read8(const std::vector<uint8_t>& buffer, uint32_t index);
	uint16_t read16(const std::vector<uint8_t>& buffer, uint32_t index);
	uint32_t read32(const std::vector<uint8_t>& buffer, uint32_t index);
	
	// STRING OPERATIONS
	// Trim strings (in place), removes white spaces from start and end of a string
	void trim(std::string& s);
	// Trim strings (in place), Remove whitespaces from end of string
	void rtrim(std::string& s);
	// Trim strings (in place), Remove whitespaces from start of string
	void ltrim(std::string& s);
	//Convert char array to string, assumes last element is null termination
	std::string get_string_from_char(const char* path);
}

#endif // MOC_UTIL_H