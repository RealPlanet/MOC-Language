#ifndef MOC_BYTEBUFFER_H
#define MOC_BYTEBUFFER_H

#include<stdlib.h>
#include<stdint.h>
#include <vector>
#include "Bytecode.h"

struct _ByteBuffer {
	std::vector<uint8_t> buffer;
	_ByteBuffer(int size) {
		buffer.reserve(size);
	}

	void write_byte8(uint8_t data);
	void write_byte16(uint16_t data);
	void write_byte32(uint32_t data);
};
typedef struct _ByteBuffer ByteBuffer;

#endif // !MOC_BYTECODE_H