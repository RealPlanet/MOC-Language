#ifndef MOC_UTIL_H
#define MOC_UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <fstream>

namespace pUtil {
	void read_ascii_file(const char* path, std::string& out_source);
	std::streamoff get_file_size(std::ifstream* stream);
}

#endif // MOC_UTIL_H