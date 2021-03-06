#include "Runtime.h"
#include "..\..\Util.h"

int Runtime::start(std::string& path)
{
	code.clear();
	pUtil::read_binary_file(path.c_str(), code);
	std::string dir_path = pUtil::get_file_path(path);

	// Reset vars to be sure everything's fine
	ip = 0;
	exit = 123;
	running = true;

	if (code.size() < 1)
		return (int)RuntimeStatus::ERROR;

	while (running) {
		InstructionPtr instruction = is.get_instruction_from_opcode(code[ip++]);
		instruction->execute(*this);
	}

	return exit;
}

void Runtime::push8(uint8_t data)
{
	stack.push(data);
}

void Runtime::push16(uint16_t data)
{
	uint8_t a = (data & 0xFF00) >> 8;
	uint8_t b = (data & 0x00FF);

	push8(a);
	push8(b);
}

void Runtime::push32(uint32_t data)
{
	uint16_t a = (data & 0xFFFF0000) >> 16;
	uint16_t b = (data & 0x0000FFFF);

	push16(a);
	push16(b);
}

uint8_t Runtime::pop8() {
	uint8_t val = stack.top();
	stack.pop();
	return val;
}

uint16_t Runtime::pop16() {
	uint16_t b = pop8();
	uint16_t a = pop8();

	return (a << 8) | b;
}

uint32_t Runtime::pop32() {
	uint16_t b = pop16();
	uint16_t a = pop16();

	return (a << 16) | b;
}