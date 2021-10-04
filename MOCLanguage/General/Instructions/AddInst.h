#ifndef MOC_ADDINST_H
#define MOC_ADDINST_H
//Includes OK
#include <iostream>
#include "../BaseClasses/Instruction/Instruction.h"
#include "../Processors/Runtime/Runtime.h"
#include "../Processors/Compiler/Compiler.h"
#include "../Tokens/TokenList/Token.h"
#include "../Tokens/TokenType/Register.h"
#include "../Processors/Sets/RegisterManager.h"

/*
*	Adds a number to a value stored in a register, saves the result in the same register.
*	Syntax: ADD %RR #N
*	
*	Errors : Bad ADD instruction - if syntax isn't respected
*/
class AddInst : public Instruction {
public:
	AddInst(int opcode) : Instruction(opcode) {}
	//Override write code write to figure out what we need to do
	virtual int write_bytecode(Compiler& compiler, ByteBuffer* bb) const override {
		const TokenList* tokens = compiler.getTokenList();
		int i = compiler.getTokenIndex();

		// ADD %RR #N
		if (tokens->get(i + 1).type == TokenType::REGISTER &&
			tokens->get(i + 2).type == TokenType::NUMBER) {
			bb->write_byte8(bytecode);
			return 0;
		}

		std::cout << tokens->get(i).line << " :Bad ADD instruction" << std::endl;
		return -1;
	}

	virtual void execute(Runtime& rt) const override {
		uint8_t a = pUtil::read8(rt.getSource(), rt.getIP()); //Bytecode of register
		uint32_t b = pUtil::read32(rt.getSource(), rt.getIP() + 1); //Value to add
		RegisterPtr reg = rt.getRegisterManager().get_reg_from_opcode(a);
		reg->stored_value += b;
		rt.incrementIPBy(5);
	}
};

#endif