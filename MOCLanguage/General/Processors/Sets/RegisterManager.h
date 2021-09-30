#ifndef MOC_REGISTERMANAGER_H
#define MOC_REGISTERMANAGER_H
#include <unordered_map>
#include "..\..\Tokens\TokenType\Register.h"

class RegisterManager {
	std::unordered_map< std::string, RegisterPtr > registers;

public:
	RegisterManager();
	void add_register(std::string reg_name, RegisterPtr _register);
	RegisterPtr get_reg(std::string reg_name) const;
	RegisterPtr get_reg_from_opcode(int code) const;
};
#endif // !MOC_REGISTERMANAGER_H

