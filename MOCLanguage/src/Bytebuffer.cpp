#include "..\include\Bytebuffer.h"

void _ByteBuffer::write_byte8(uint8_t data)
{
	buffer.push_back(data);
}

void _ByteBuffer::write_byte16(uint16_t data)
{
	uint8_t a = (data & 0xFF00) >> 8;
	uint8_t b = (data & 0xFF);

	write_byte8(a);
	write_byte8(b);
}

void _ByteBuffer::write_byte32(uint32_t data)
{
	uint16_t a = (data & 0xFFFF0000) >> 16;
	uint16_t b = (data & 0x0000FFFF);

	write_byte16(a);
	write_byte16(b);
}
