#ifndef MOC_BYTEBUFFER_H
#define MOC_BYTEBUFFER_H
#include <vector>
#include <iostream>
struct _ByteBuffer {
	std::vector<uint8_t> buffer;
	_ByteBuffer(int size) {
		buffer.reserve(size);
	}

	// Added replaceAt functionality for labels, note to self, should i make standalone methods for that?
	void write_byte8(uint8_t data, bool replaceAt = false, int index = -1);
	void write_byte16(uint16_t data, bool replaceAt = false, int index = -1);
	void write_byte32(uint32_t data, bool replaceAt = false, int index = -1);
	inline std::size_t buffer_index() { return buffer.size(); }

	//DEBUG FUNCTION
	void print_bytebuffer_console();
};
typedef struct _ByteBuffer ByteBuffer;

#endif // !MOC_BYTECODE_H