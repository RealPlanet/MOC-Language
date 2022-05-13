#ifndef MOC_INSTRUCTIONTYPE_H
#define MOC_INSTRUCTIONTYPE_H

// Parameter order
enum class InstType {
	RR = 0x00,	// Register - Register
	NN,
	RN,			// Register - Number
	NR,			// Number - Register
	R,			// Register
	N,			// Number
	S			// String
};

#endif // !MOC_INSTRUCTIONTYPE_H

