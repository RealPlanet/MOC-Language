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

* `NOP`     - Fallback OPCODE not used, will stop parsing and/or bytecode compile

## Available Registers (prefix with % in code)
* `eax`    - Push 8 bit number onto the stack