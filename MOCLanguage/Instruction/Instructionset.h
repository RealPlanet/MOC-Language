#ifndef MOC_INSTRUCTIONSET_H
#define MOC_INSTRUCTIONSET_H

#include <unordered_map>
#include <string>
#include <typeinfo>

#include "PushInst.h"
#include "Instruction.h"

class Instructionset
{
private:
	std::unordered_map<std::string, InstructionPtr > instruction_codes;
public:
	Instructionset();
	void register_instruction(std::string name, InstructionPtr instruction);
	InstructionPtr get_instruction(const std::string name) const;
};
#endif // !MOC_INSTRUCTIONSET_H



