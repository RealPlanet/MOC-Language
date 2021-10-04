#ifndef MOC_UTIL_H
#define MOC_UTIL_H
//Includes OK
#include <vector>
#include <string>
#include "Processors/Compiler/Bytebuffer.h"

namespace pUtil {
	void read_ascii_file(const char* path, std::string& out_source);
	void read_binary_file(const char* path, std::vector<uint8_t>& out_code);
	uint32_t get_number32(const std::string& buf);
	int get_number(const std::string& buf);
	std::streamoff get_file_size(std::ifstream* stream);
	void write_binary_file(std::string path, ByteBuffer& bb);

	//Create folder at path
	bool create_folder(std::string name, std::string path);

	// Read 8/16/32 bits from a buffer at index
	uint8_t read8(const std::vector<uint8_t>& buffer, uint32_t index);
	uint16_t read16(const std::vector<uint8_t>& buffer, uint32_t index);
	uint32_t read32(const std::vector<uint8_t>& buffer, uint32_t index);

	void trim(std::string& s);
	void rtrim(std::string& s);
	void ltrim(std::string& s);

	//Convert char array to string, assumes last element is null termination
	std::string get_string_from_char(const char* path);

	// Returns file path without the file name included
	std::string get_file_path(const std::string& path);
	std::string get_file_path(const char* path);
}

#endif // MOC_UTIL_H