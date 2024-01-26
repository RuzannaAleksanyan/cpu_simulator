#include "cpu.h"
#include "alu.h"

enum Instruction { MOV, ADD, SUB, MUL, DIV, AND, OR, NOT, CMP, JMP, JG, JL, JE, PRINT };

void cpu_execute(struct CPU* cpu, int address) {
    for(int i = 0; i < address; ++i) {
        decode(cpu, cpu->memory[i]);
    }
}

void decode(struct CPU* cpu, short code) {
    int instruction = (code >> 12) & 0b11;   // 4 bit for instruction
    int op1_value = (code >> 8) & 0b1111;   // 4 bits for op1 value
    int op1_category = (code >> 6) & 0b11;   // 2 bit for op1 category
    int op2_value = (code >> 2) & 0b1111;   // 4 bits for op2 value
    int op2_category = code & 0b11;         // 2 bits for op2 category

    if(instruction == MOV) {
        alu_mov(cpu, op1_value, op1_category, op2_value, op2_category);
    } else if(instruction == ADD) {
        // alu_add(cpu, op1_value, op1_category, op2_value, op2_category);
    } else if(instruction == SUB) {
        // alu_sub(cpu, op1_value, op1_category, op2_value, op2_category);
    } else if(instruction == MUL) {
        // alu_mul(cpu, op1_value, op1_category, op2_value, op2_category);
    } else if(instruction == DIV) {
        // alu_div(cpu, op1_value, op1_category, op2_value, op2_category);
    } else if(instruction == AND) {
        // alu_and(cpu, op1_value, op1_category, op2_value, op2_category);
    } else if(instruction == OR) {
        // alu_or(cpu, op1_value, op1_category, op2_value, op2_category);
    } else if(instruction == CMP) {
        // alu_cmp(cpu, op1_value, op1_category, op2_value, op2_category);
    } 
    // else if(instruction == ADD) {
    //     alu_add(cpu, op1_value, op1_category, op2_value, op2_category);
    // } else if(instruction == ADD) {
    //     alu_add(cpu, op1_value, op1_category, op2_value, op2_category);
    // } else if(instruction == ADD) {
    //     alu_add(cpu, op1_value, op1_category, op2_value, op2_category);
    // } else if(instruction == ADD) {
    //     alu_add(cpu, op1_value, op1_category, op2_value, op2_category);
    // } else if(instruction == ADD) {
    //     alu_add(cpu, op1_value, op1_category, op2_value, op2_category);
    // }
}