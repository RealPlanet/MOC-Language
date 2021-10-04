#ifndef MOC_INSTRUCTIONSET_H
#define MOC_INSTRUCTIONSET_H
//Includes OK
#include <unordered_map>
#include "..\..\BaseClasses\Instruction\Instruction.h"

class Instructionset
{
private:
	// Holds all instruction types
	std::unordered_map< std::string, InstructionPtr > instruction_codes_name;
	std::unordered_map< int, InstructionPtr > instruction_codes_opcode;
public:
	//Register available instructions, must heap allocate so i can cast them to Instruction if any derived class is used!
	Instructionset();

	//Register a new instruction in the set
	void register_instruction(std::string name, InstructionPtr instruction);

	//Fetch the instruction from the set or return nop if not defined!
	InstructionPtr get_instruction(const std::string name) const;
	InstructionPtr get_instruction_from_opcode(int opcode) const;

};
#endif // !MOC_INSTRUCTIONSET_H



