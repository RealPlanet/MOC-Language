#include "Instructionset.h"
#include <stdexcept>

void Instructionset::register_instruction(const std::string name, const Instruction* instruction) {
	instruction_codes[name] = instruction;
}

const Instruction* Instructionset::get_instruction(const std::string name) const {
	try {
		return instruction_codes.at(name);
	}
	// Return NoOperation code
	catch (std::out_of_range) {
		return instruction_codes.at("nop");
	}

}

Instructionset::Instructionset() {
	register_instruction("nop", new Instruction(0x00));
	register_instruction("push", new Instruction(0x01));
	register_instruction("add", new Instruction(0x02));
	register_instruction("hlt", new Instruction(0xFF));
}