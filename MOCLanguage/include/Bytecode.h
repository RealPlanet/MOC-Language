#ifndef MOC_BYTECODE_H
#define MOC_BYTECODE_H

enum _Bytecode {
	NOP = 0X00,
	PUSH_CONST = 0x01,
	ADD_STACK = 0x02,
	HLT_OP = 0xFF
};

typedef enum _Bytecode Bytecode;

#endif // !MOC_BYTECODE_H
