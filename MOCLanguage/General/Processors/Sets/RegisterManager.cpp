#include "RegisterManager.h"
#include <stdexcept>

RegisterManager::RegisterManager()
{
	add_register("eax", std::make_shared<Register>(0x00));
}

void RegisterManager::add_register(std::string reg_name, RegisterPtr _register){
	registers[reg_name] = _register;
}

RegisterPtr RegisterManager::get_reg(std::string reg_name) const
{
	try {
		return registers.at(reg_name);
	}
	// Return nullptr, register doesn't exist
	catch (std::out_of_range) {
		return nullptr;
	}
}

RegisterPtr RegisterManager::get_reg_from_opcode(int code) const
{
	for (auto entry : registers) {
		if (entry.second.get()->bytecode == code)
			return entry.second;
	}

	return nullptr;
}
