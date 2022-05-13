#ifndef MOC_PRINTS_H
#define MOC_PRINTS_H
//Includes OK
#include "../BaseClasses/Instruction/Instruction.h"

/*
* Print's a numeric constant to the console
* Syntax: HLT
*/
class PrintString : public Instruction {
public:
	PrintString(int opcode) : Instruction(opcode) {}
	virtual int write_bytecode(Compiler& compiler, ByteBuffer* bb) const override {
		bb->write_byte8(bytecode);

		const TokenList* tokens = compiler.getTokenList();
		int i = compiler.getTokenIndex();
		/*
		if (tokens->get(i + 1).type == TokenType::STRING) {
			bb->write_byte8((uint8_t)InstType::S);
		}
		else {
			std::cout << tokens->get(i).line << " : Bad PRINTI instruction, wrong parameter given" << std::endl;
			return 1;
		}*/

		return 0;
	}

	virtual void execute(Runtime& rt) const override {
		InstType type = (InstType)pUtil::read8(rt.getSource(), rt.getIP());
		int size = pUtil::read32(rt.getSource(), rt.getIP() + 1);

		if (type == InstType::S) {	
			rt.incrementIPBy(2); // Bring the IP up to speed.

			std::string readString = "";

			for (int i = 0; i < size; i++) {
				readString += ((char)pUtil::read32(rt.getSource(), rt.getIP() + i));
			}

			std::cout << readString << std::endl;
		}
		else {
			std::cout << "Runtime exception :: Parameter type not found for prints instruction" << std::endl;
		}
		
		rt.incrementIPBy(size);
	}
};

#endif //!MOC_PRINTS_H