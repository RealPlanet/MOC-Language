#ifndef MOC_REGISTERMANAGER_H
#define MOC_REGISTERMANAGER_H
#include <unordered_map>
#include "..\..\Tokens\TokenDefinition\Register.h"

/*
* Stores all registers and provides getter from name or opcode
* 
* TODO :: Update class to have a second map to avoid a linear search in "get_reg_from_opcode"
*/

class RegisterManager {
	std::unordered_map< std::string, RegisterPtr > registers;

public:
	RegisterManager();
	void add_register(std::string reg_name, RegisterPtr _register);
	RegisterPtr get_reg(std::string reg_name) const;
	RegisterPtr get_reg_from_opcode(int code) const;
};
#endif // !MOC_REGISTERMANAGER_H

