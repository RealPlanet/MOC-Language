#ifndef MOC_MOVNST_H
#define MOC_MOVNST_H
//Includes OK
#include "../BaseClasses/Instruction/Instruction.h"
#include "../Tokens/TokenList/Token.h"
#include "../Processors/Runtime/Runtime.h"
#include <iostream>


class MovInst : public Instruction {
public:
	MovInst(int opcode) : Instruction(opcode) {}
	//Override write code write to figure out what we need to do
	virtual int write_bytecode(ByteBuffer* bb, const TokenList* tokens, const int i) const override {
		// MOV %RR #N
		if (tokens->get(i + 1).type == TokenType::REGISTER &&
			tokens->get(i + 2).type == TokenType::NUMBER) {
			bb->write_byte8(bytecode);
			return 0;
		}
		std::cout << tokens->get(i).line << " :Bad MOV instruction" << std::endl;
		return -1;
	}

	virtual void execute(Runtime& rt, const RegisterManager& regMan, const std::vector<uint8_t>& code) const override {
		rt.incrementIPBy(5);
	}
};

#endif //!MOC_MOVNST_H