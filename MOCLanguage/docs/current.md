# MOC VM Spec

## Symbols

`#` means number constant
`%` means register

## Instructions
* `PUSH`    - Push 8 bit number onto the stack

* `ADD`		- %<Register> #<Number> Adds number to value stored in register

* `SUB`		- Pops last two numbers off of stack, subtracts, pushes result

* `MUL`		- Pops last two numbers off of stack, multiplies, pushes result

* `HLT`     - Pops stack and returns result as exit code -- NOT FINAL

* `JMP`     - Jumps to given label, syntax: JMP <Name>

* `NOP`     - Fallback OPCODE not used, will stop parsing and/or bytecode compile

## Available Registers (prefix with % in code)
* `eax`    - Push 8 bit number onto the stack

## Labels
The label table is generated on compile time (after parser has scanned the code), once the compiler has finished the bytecode will be writte to file in the following fashion:
First 32 bits rapresent the IP value that the interpreter needs to jump to on start. The following values will rapresent the labels