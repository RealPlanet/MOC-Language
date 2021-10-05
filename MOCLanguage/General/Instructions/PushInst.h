#ifndef MOC_PUSHINST_H
#define MOC_PUSHINST_H
//Includes OK
#include "../BaseClasses/Instruction/Instruction.h"
#include "../Processors/Parser/InstructionType/InstructionType.h"
#include "../Processors/Compiler/Compiler.h"
#include "../Processors/Runtime/Runtime.h"

#include "../Util.h"
#include "../Tokens/TokenList/Token.h"
#include "../Tokens/TokenType/Register.h"
#include "../Processors/Sets/RegisterManager.h"
/*
*	Pushes a numeric constant on top of the stack
* 
*	Syntax: PUSH #N
*/
class PushInst : public Instruction {
public:
	PushInst(int opcode) : Instruction(opcode) {}
	virtual int write_bytecode(Compiler& compiler, ByteBuffer* bb) const override {
		bb->write_byte8(bytecode);

		const TokenList* tokens = compiler.getTokenList();
		int i = compiler.getTokenIndex();

		if (tokens->get(i + 1).type == TokenType::REGISTER) {
			bb->write_byte8((uint8_t)InstType::R);
		}
		else if (tokens->get(i + 1).type == TokenType::NUMBER) {
			bb->write_byte8((uint8_t)InstType::N);
		}
		else {
			std::cout << tokens->get(i).line << " : Bad PUSH instruction, wrong parameter given" << std::endl;
			return 1;
		}

		return 0;
	}

	virtual void execute(Runtime& rt) const override {
		InstType type = (InstType)pUtil::read8(rt.getSource(), rt.getIP());
		int ip_inc = 1; // Base amount, instruction type;

		switch (type) {
			case InstType::R: {
				uint8_t regCode = pUtil::read8(rt.getSource(), rt.getIP() + 1);
				RegisterPtr reg = rt.getRegisterManager().get_reg_from_opcode(regCode);
				rt.push32(reg->stored_value);
				ip_inc += 1; // Register code is 8 bit long
				break;
			}
			case InstType::N: {
				rt.push32(pUtil::read32(rt.getSource(), rt.getIP() + 1));
				ip_inc += 4; // Data is 32 bit long

				break;
			}
			default:
				std::cout << "Runtime exception :: Parameter type not found for push instruction" << std::endl;
		}

		// InstType (1) 
		rt.incrementIPBy(ip_inc);
	}
};

#endif