
#ifndef MOC_RUNTIME_H
#define MOC_RUNTIME_H
#include <vector>
#include <stack>

enum class _RuntimeStatus {
	SUCCESS,
	ERROR = -1
};
typedef enum _RuntimeStatus RuntimeStatus;

class Instructionset;
class Runtime {
private:
	std::vector<uint8_t> code;
	std::stack<uint8_t> stack;
	bool running = false;

	// Instruction pointer
	uint32_t ip = 0;
	uint8_t exit = 123;
public:
	Runtime(std::vector<uint8_t> newCode) : code{ newCode } {}
	int start();
	// Instruction pointer functions
	inline void incrementIPBy(int inc) { ip += inc; }
	inline uint32_t getIP() { return ip; }

	// Exit code
	inline void setExitCode(uint8_t code) { exit = code; }
	inline void setRunningStatus(bool isRunning) { running = isRunning; }
	inline int stackSize() { return stack.size(); }
	//Stack functions
	void push8(uint8_t data);
	void push16(uint16_t data);
	void push32(uint32_t data);

	uint8_t  pop8();
	uint16_t pop16();
	uint32_t pop32();
};

#endif // MOC_RUNTIME_H