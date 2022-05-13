#ifndef MOC_CMPINST_H
#define MOC_CMPINST_H
//Includes OK
#include <algorithm>
#include "../BaseClasses/Instruction/Instruction.h"
#include "../Processors/Runtime/Runtime.h"
#include "../Processors/Compiler/Compiler.h"
#include "../Util.h"
/*
*  Jumps to given label.
*
*  Syntax: JMP @<name>
*/
class CmpInst : public Instruction {
protected:
	static void print_argument_error(int arg_line, int arg_position) {
		std::cout << "Error at line " << arg_line << " : Bad CMP instruction, wrong parameter (#" << 1 << ") given" << std::endl;
	}
	
	static int write_cmp_data(Compiler& compiler, ByteBuffer* bb) {
		const TokenList* tokens = compiler.getTokenList();
		int i = compiler.getTokenIndex();
		bool first_is_register = tokens->get(i + 1).type == TokenType::REGISTER;
		bool second_is_register = tokens->get(i + 2).type == TokenType::REGISTER;
		
		if (!first_is_register && tokens->get(i + 1).type != TokenType::NUMBER) {
			print_argument_error(tokens->get(i + 1).line, 1);
			return 1;
		}
		
		if (!second_is_register && tokens->get(i + 2).type != TokenType::NUMBER) {
			print_argument_error(tokens->get(i + 2).line, 2);
			return 1;
		}

		if (first_is_register && second_is_register) {
			bb->write_byte8((uint8_t)InstType::RR);
			return 0;
		}

		if (first_is_register && !second_is_register) {
			bb->write_byte8((uint8_t)InstType::RN);
			return 0;
		}

		if (!first_is_register && second_is_register) {
			bb->write_byte8((uint8_t)InstType::NR);
			return 0;
		}

		bb->write_byte8((uint8_t)InstType::NN);
		return 0;
	}
public:
	CmpInst(int opcode) : Instruction(opcode) {}
	virtual int write_bytecode(Compiler& compiler, ByteBuffer* bb) const override {
		Instruction::write_bytecode(compiler, bb);
		write_cmp_data(compiler, bb);
		return 0;
	}

	virtual void execute(Runtime& rt) const override {
		InstType op_type = (InstType)pUtil::read8(rt.getSource(), rt.getIP());
		int ip_inc = 1;
		uint32_t valueA = 0, valueB = 0;

		switch (op_type)
		{
		case InstType::RR: {
			uint8_t reg_one_code = pUtil::read8(rt.getSource(), rt.getIP() + 1);
			uint8_t reg_two_code = pUtil::read8(rt.getSource(), rt.getIP() + 2);
			valueA = rt.getRegisterManager().get_reg_from_opcode(reg_one_code)->stored_value;
			valueB = rt.getRegisterManager().get_reg_from_opcode(reg_two_code)->stored_value;
			ip_inc += 2;
			break;
		}
		case InstType::NN: {
			valueA = pUtil::read32(rt.getSource(), rt.getIP() + 1);
			valueB = pUtil::read32(rt.getSource(), rt.getIP() + 5);
			ip_inc += 8;
			break; 
		}
		case InstType::RN: {
			uint8_t  reg_one_code = pUtil::read8(rt.getSource(), rt.getIP() + 1);
			valueA = rt.getRegisterManager().get_reg_from_opcode(reg_one_code)->stored_value;
			valueB = pUtil::read32(rt.getSource(), rt.getIP() + 2);
			ip_inc += 5;
			break;
		}
		case InstType::NR: {
			uint8_t reg_two_code = pUtil::read8(rt.getSource(), rt.getIP() + 5);
			valueA = pUtil::read32(rt.getSource(), rt.getIP() + 1);
			valueB = rt.getRegisterManager().get_reg_from_opcode(reg_two_code)->stored_value;
			ip_inc += 5;
			break;
		}
		default:
			std::cout << "Unknown CMP operation time, aborting!" << "\n";
			rt.setRunningStatus(false);
			return;
		}

		bool result = valueA - valueB == 0;
		
		rt.getMathRegister().update(Flags::ZERO,	(int)result);
		//Not sure on carry update
		rt.getMathRegister().update(Flags::CARRY,	(int)!result);

		rt.incrementIPBy(ip_inc);
	}
};

#endif // !MOC_CMPINST_H