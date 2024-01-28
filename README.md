# CPU Simulator in C
## Overview
This project involves building a CPU simulator in C that emulates the basic functionalities of a Central Processing Unit. The simulator supports six general-purpose registers, arithmetic and logic operations, conditional and unconditional jumps, memory operations, and a dump_memory() function to display memory contents.

## Instruction Set
The CPU supports the following instructions:
- **MOV**: Move data between registers or between a register and memory.
- **ADD**: Addition operation.
- **SUB**: Subtraction operation.
- **MUL**: Multiplication operation.
- **DIV**: Division operation.
- **AND**: Bitwise AND operation.
- **OR**: Bitwise OR operation.
- **NOT**: Bitwise NOT operation.
- **CMP**: Comparison operation.
- **JMP**: Unconditional jump.
- **JG**: Jump if greater.
- **JL**: Jump if less.
- **JE**: Jump if equal.

## Registers
The CPU has six general-purpose registers:
- AYB
- BEN
- GIM
- DA
- ECH
- ZA

## Compilation and Execution
To compile and run the program:
```bash
gcc cpu_simulator.c -o cpu_simulator
./cpu_simulator input_file.txt
```
Replace `input_file.txt` with the path to your assembly code file.
