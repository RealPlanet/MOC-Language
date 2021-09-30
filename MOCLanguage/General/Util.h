#ifndef MOC_UTIL_H
#define MOC_UTIL_H
//Includes OK
#include <vector>
#include <string>
#include "Processors/Compiler/Bytebuffer.h"

namespace pUtil {
	void read_ascii_file(const char* path, std::string& out_source);
	void read_binary_file(const char* path, std::vector<uint8_t>& out_code);
	uint32_t get_number(const std::string& buf);
	std::streamoff get_file_size(std::ifstream* stream);
	void write_binary_file(std::string path, ByteBuffer& bb);
	uint8_t read8(const std::vector<uint8_t>& buffer, uint32_t index);
	uint16_t read16(const std::vector<uint8_t>& buffer, uint32_t index);
	uint32_t read32(const std::vector<uint8_t>& buffer, uint32_t index);
}

#endif // MOC_UTIL_H