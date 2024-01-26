#include "cpu.h"

void cpu_execute(struct CPU* cpu, int address) {
    for(int i = 0; i < address; ++i) {
        decode(cpu, cpu->memory[i]);
    }
}

void decode(struct CPU* cpu, short code) {
    int instruction = (code >> 12) & 0b1;   // 1 bit for instruction
    int op1_value = (code >> 8) & 0b1111;   // 4 bits for op1 value
    int op1_category = (code >> 7) & 0b1;   // 1 bit for op1 category
    int op2_value = (code >> 3) & 0b1111;   // 4 bits for op2 value
    int op2_category = code & 0b11;         // 2 bits for op2 category

    // // Now you can use these values as needed
    // printf("Instruction: %d\n", instruction);
    // printf("Op1 Value: %d\n", op1_value);
    // printf("Op1 Category: %d\n", op1_category);
    // printf("Op2 Value: %d\n", op2_value);
    // printf("Op2 Category: %d\n", op2_category);
}