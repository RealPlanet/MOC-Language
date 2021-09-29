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
	std::unordered_map<std::string, const Instruction* > instruction_codes;
public:
	Instructionset();
	void register_instruction(std::string name, const Instruction* instruction);
	const Instruction* get_instruction(const std::string name) const;
};
#endif // !MOC_INSTRUCTIONSET_H



