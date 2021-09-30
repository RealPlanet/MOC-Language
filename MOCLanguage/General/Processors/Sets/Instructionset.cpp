#include "Instructionset.h"
#include <stdexcept>

void Instructionset::register_instruction(const std::string name, InstructionPtr instruction) {
	instruction_codes_name[name] = instruction;
}

// TODO :: Invert these two so runtime is faster -- How would i inspect the bytecode for the keys?
InstructionPtr Instructionset::get_instruction(const std::string name) const {
	try {
		return instruction_codes_name.at(name);
	}
	// Return NoOperation code
	catch (std::out_of_range) {
		return instruction_codes_name.at("nop");
	}
}

InstructionPtr Instructionset::get_instruction_from_opcode(int opcode) const
{
	try {
		return instruction_codes_opcode.at(opcode);
	}
	// Return NoOperation code
	catch (std::out_of_range) {
		return instruction_codes_name.at("nop");
	}
}

/*
* Register available instructions, must heap allocate so i can cast them to Instruction if any derived class is used!
*
* Syntax: string : Instruction name - shared_pointer<Instruction>(OPCODE)
*/
#include "../../Instructions/PushInst.h"
#include "../../Instructions/AddInst.h"
#include "../../Instructions/HltInst.h"
#include "../../Instructions/SubInst.h"
#include "../../Instructions/MulInst.h"
#include "../../Instructions/MovInst.h"

Instructionset::Instructionset() {
	register_instruction("nop",		std::make_shared<Instruction>(0x00));
	register_instruction("push",	std::make_shared<PushInst>(0x01));
	register_instruction("add",		std::make_shared<AddInst>(0x02));
	register_instruction("sub",		std::make_shared<SubInst>(0x03));
	register_instruction("mul",		std::make_shared<MulInst>(0x04));
	register_instruction("mov",		std::make_shared<MovInst>(0x05));

	register_instruction("hlt",		std::make_shared<HltInst>(0xFF));

	for (auto val : instruction_codes_name) {
		instruction_codes_opcode[val.second->bytecode] = val.second;
	}
}