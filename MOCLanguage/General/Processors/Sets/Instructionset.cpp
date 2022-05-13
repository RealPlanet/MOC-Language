#include "Instructionset.h"
#include <stdexcept>

void InstructionSet::register_instruction(const std::string name, InstructionPtr instruction) {
	instruction_codes_name[name] = instruction;
}
InstructionPtr InstructionSet::get_instruction(const std::string name) const {
	try {
		return instruction_codes_name.at(name);
	}
	// Return NoOperation code
	catch (std::out_of_range) {
		return instruction_codes_name.at("nop");
	}
}
InstructionPtr InstructionSet::get_instruction_from_opcode(int opcode) const
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
#include "../../Instructions/ConditionalInstructions/PushConditional.h"
#include "../../Instructions/AddInst.h"
#include "../../Instructions/HltInst.h"
#include "../../Instructions/SubInst.h"
#include "../../Instructions/MulInst.h"
#include "../../Instructions/MovInst.h"
#include "../../Instructions/JmpInst.h"
#include "../../Instructions/PrintIInst.h"
#include "../../Instructions/PrintStringInst.h"
#include "../../Instructions/CmpInst.h"

InstructionSet::InstructionSet() {
	int inst_counter = 0x00;
	register_instruction("nop",		std::make_shared<Instruction>	(inst_counter++)	);

	//Stack instructions
	register_instruction("push",	std::make_shared<PushInst>(inst_counter++)	);
	register_instruction("pushe",	std::make_shared<PushConditional>(inst_counter++, InstCondition::EQUAL)	);

	//Math instructions
	register_instruction("add",		std::make_shared<AddInst>		(inst_counter++)	);
	register_instruction("sub",		std::make_shared<SubInst>		(inst_counter++)	);
	register_instruction("mul",		std::make_shared<MulInst>		(inst_counter++)	);
	register_instruction("mov",		std::make_shared<MovInst>		(inst_counter++)	);

	//Logic instructions
	register_instruction("jmp",		std::make_shared<JmpInst>		(inst_counter++)	);
	register_instruction("printi",	std::make_shared<PrintIInst>	(inst_counter++)	);
	register_instruction("prints",	std::make_shared<PrintString>	(inst_counter++)	);
	register_instruction("cmp",		std::make_shared<CmpInst>		(inst_counter++)	);


	register_instruction("hlt",		std::make_shared<HltInst>		(0xFF)	);

	for (auto val : instruction_codes_name) {
		instruction_codes_opcode[val.second->bytecode] = val.second;
	}
}