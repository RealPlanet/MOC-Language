# MOC VM Spec

## Symbols

`#` means number constant

## Instructions
* `PUSH`    - Push 8 bit number onto the stack
* `ADD`		- Pops last two numbers off of stack, adds, pushes result
* `SUB`		- Pops last two numbers off of stack, subtracts, pushes result
* `MUL`		- Pops last two numbers off of stack, multiplies, pushes result
* `HLT`     - Pops stack and returns result as exit code -- NOT FINAL
* `NOP`     - Fallback OPCODE not used, will stop parsing and/or bytecode compile