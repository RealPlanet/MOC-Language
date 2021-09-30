#ifndef MOC_ADDINST_H
#define MOC_ADDINST_H
//Includes OK
#include "../BaseClasses/Instruction/Instruction.h"
#include "../Processors/Runtime/Runtime.h"
#include "../Tokens/TokenList/Token.h"
#include <iostream>
#include "../Tokens/TokenType/Register.h"
#include "../Processors/Sets/RegisterManager.h"

class AddInst : public Instruction {
public:
	AddInst(int opcode) : Instruction(opcode) {}
	//Override write code write to figure out what we need to do
	virtual int write_bytecode(ByteBuffer* bb, const TokenList* tokens, const int i) const override {
		// ADD %RR #N
		if (tokens->get(i + 1).type == TokenType::REGISTER &&
			tokens->get(i + 2).type == TokenType::NUMBER) {
			bb->write_byte8(bytecode);
			return 0;
		}

		std::cout << tokens->get(i).line << " :Bad ADD instruction" << std::endl;
		return -1;
	}

	virtual void execute(Runtime& rt, const RegisterManager& regMan, const std::vector<uint8_t>& code) const override {
		uint8_t a = pUtil::read8(code, rt.getIP()); //Bytecode of register
		uint32_t b = pUtil::read32(code, rt.getIP() + 1); //Value to add
		RegisterPtr reg = regMan.get_reg_from_opcode(a);
		reg->stored_value += b;
		rt.incrementIPBy(5);
	}
};

#endif