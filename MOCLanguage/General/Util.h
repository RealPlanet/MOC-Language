#ifndef MOC_UTIL_H
#define MOC_UTIL_H
#include "..\Compiler\Bytebuffer.h"
#include <stdio.h>
#include <stdlib.h>
#include <fstream>

namespace pUtil {
	void read_ascii_file(const char* path, std::string& out_source);
	void read_binary_file(const char* path, std::vector<uint8_t>& out_code);
	std::streamoff get_file_size(std::ifstream* stream);
	void write_binary_file(std::string path, ByteBuffer& bb);
	uint16_t read16(const std::vector<uint8_t>& buffer, uint32_t index);
	uint32_t read32(const std::vector<uint8_t>& buffer, uint32_t index);
}

#endif // MOC_UTIL_H