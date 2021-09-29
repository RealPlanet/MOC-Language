#ifndef MOC_UTIL_H
#define MOC_UTIL_H
#include "..\Compiler\Bytebuffer.h"
#include <stdio.h>
#include <stdlib.h>
#include <fstream>

namespace pUtil {
	void read_ascii_file(const char* path, std::string& out_source);
	std::streamoff get_file_size(std::ifstream* stream);
	void write_binary_file(std::string path, ByteBuffer& bb);
}

#endif // MOC_UTIL_H