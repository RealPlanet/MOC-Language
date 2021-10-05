#include "Bytebuffer.h"

void _ByteBuffer::write_byte8(uint8_t data, bool replaceAt, int index)
{
	if (replaceAt) {
		buffer[index] = data;
		return;
	}

	buffer.push_back(data);
}

void _ByteBuffer::write_byte16(uint16_t data, bool replaceAt, int index)
{
	uint8_t a = (data & 0xFF00) >> 8;
	uint8_t b = (data & 0xFF);

	write_byte8(a, replaceAt, index);
	write_byte8(b, replaceAt, index + 1);
}

void _ByteBuffer::write_byte32(uint32_t data, bool replaceAt, int index)
{
	uint16_t a = (data & 0xFFFF0000) >> 16;
	uint16_t b = (data & 0x0000FFFF);

	write_byte16(a, replaceAt, index);
	write_byte16(b, replaceAt, index + 2);
}

void _ByteBuffer::print_bytebuffer_console()
{
	system("cls");

	for (auto val : buffer) {
		std::cout << std::hex << (int)val << std::endl;
	}
}
