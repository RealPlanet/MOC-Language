#include "Instructionset.h"
#include <stdexcept>

void Instructionset::register_instruction(const std::string name, InstructionPtr instruction) {
	instruction_codes_name[name] = instruction;
}
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
#include "../../Instructions/JmpInst.h"
#include "../../Instructions/PrintIInst.h"
#include "../../Instructions/CmpInst.h"

// NOTE TO SELF :: This is needless work, should switch it up to be a enum so opcode is automatically defined
Instructionset::Instructionset() {
	register_instruction("nop",		std::make_shared<Instruction>(0x00));

	register_instruction("push",	std::make_shared<PushInst>(0x01));
	register_instruction("pushe",	std::make_shared<PushInst>(0x01, InstCondition::EQUAL));


	register_instruction("add",		std::make_shared<AddInst>(0x02));
	register_instruction("sub",		std::make_shared<SubInst>(0x03));
	register_instruction("mul",		std::make_shared<MulInst>(0x04));
	register_instruction("mov",		std::make_shared<MovInst>(0x05));
	register_instruction("jmp",		std::make_shared<JmpInst>(0x06));
	register_instruction("printi",	std::make_shared<PrintIInst>(0x07));

	register_instruction("cmp",		std::make_shared<CmpInst>(0x09));

	register_instruction("hlt",		std::make_shared<HltInst>(0xFF));

	for (auto val : instruction_codes_name) {
		instruction_codes_opcode[val.second->bytecode] = val.second;
	}
}