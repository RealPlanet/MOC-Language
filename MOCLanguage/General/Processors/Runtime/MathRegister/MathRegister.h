#pragma once
enum Flags {
	CARRY = 0,
	NEGATIVE,
	ZERO,
	V //Overflow
};

class MathRegister
{

private:
	int reg[16];

public:
	inline int value(int i) { return reg[i]; }

	inline void init_register() {
		for (int i = 0; i < 16; i++)
			reg[i] = 0;
	}

	inline void update(int index, int value) {
		reg[index] = value;
	}
};

