
#ifndef MOC_RUNTIME_H
#define MOC_RUNTIME_H
#include <vector>
#include <stack>
#include "../Sets/LabelTable.h"
#include "../../Processors/Sets/Instructionset.h"
#include "../Sets/RegisterManager.h"

enum class _RuntimeStatus {
	SUCCESS,
	ERROR = -1
};
typedef enum _RuntimeStatus RuntimeStatus;

class Instructionset;
class Runtime {
private:
	Instructionset is;
	RegisterManager regMan;
	Labels::LabelTable label_table;

	std::vector<uint8_t> code;
	std::stack<uint8_t> stack;
	

	bool running = false;

	// Instruction pointer
	uint32_t ip = 0;
	uint8_t exit = 123;
public:
	Runtime() {}
	int start(std::string& path);
	// Instruction pointer functions
	inline void incrementIPBy(int inc) { ip += inc; }
	inline void decrementIPBy(int inc) { ip -= inc; }
	inline void setIPBy(int num) { ip = num; }
	inline uint32_t getIP() { return ip; }

	// Sets getters
	inline Labels::LabelTable& getLabelTable() { return label_table; }
	inline RegisterManager& getRegisterManager() { return regMan; }
	// Code getter
	inline std::vector<uint8_t> getSource() { return code; }
	
	// Exit code
	inline void setExitCode(uint8_t code) { exit = code; }
	inline void setRunningStatus(bool isRunning) { running = isRunning; }
	inline std::size_t stackSize() { return stack.size(); }
	//Stack functions
	void push8(uint8_t data);
	void push16(uint16_t data);
	void push32(uint32_t data);

	uint8_t  pop8();
	uint16_t pop16();
	uint32_t pop32();
};

#endif // MOC_RUNTIME_H