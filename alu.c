#include "alu.h"
#include "cpu.h"

#include <stdio.h>

enum Operand { AYB, BEN, GIM, DA, ECH, ZA};

void alu_initialize(struct ALU* alu, struct CPU* parent_cpu) {
    alu->parent_cpu = parent_cpu;
}

void alu_mov(struct CPU* cpu, int op1_value, int op1_category, int op2_value, int op2_category) {
    if(op1_category == 3 && op2_category == 3) {
        alu_mov_reg_reg(cpu, op1_value, op2_value);
    } else if(op1_category == 3 && op2_category == 0) {
        alu_mov_reg_mem(cpu, op1_value, op2_value);
    } else if(op1_category == 3 && op2_category == 2) {
        alu_mov_reg_lit(cpu, op1_value, op2_value);
    } else if(op1_category == 0 && op2_category == 3) {
        alu_mov_mem_reg(cpu, op1_value, op2_value);
    } else if(op1_category == 0 && op2_category == 0) {
        alu_mov_mem_mem(cpu, op1_value, op2_value);
    } else if(op1_category  == 0 && op2_category == 2) {
        alu_mov_mem_lit(cpu, op1_value, op2_value);
    } else {
        // Handle Invalid Operands
    }
}

void alu_mov_mem_lit(struct CPU* cpu, int op1_value, int op2_value) {
    cpu->memory[op1_value] = op2_value;
}

void alu_mov_mem_mem(struct CPU* cpu, int op1_value, int op2_value) {
    cpu->memory[op1_value] = cpu->memory[op2_value];
}

void alu_mov_mem_reg(struct CPU* cpu, int op1_value, int op2_value) {
    int value = 0;

    switch (op2_value) {
        case 0:
            value = cpu->registers.AYB;
            break;
        case 1:
            value = cpu->registers.BEN;
            break;
        case 2:
            value = cpu->registers.GIM;
            break;
        case 3:
            value = cpu->registers.DA;
            break;
        case 4:
            value = cpu->registers.ECH;
            break;
        case 5:
            value = cpu->registers.ZA;
            break;
        default:
            // Handle invalid op1_value
            return;
    }

    cpu->memory[op1_value] = value;
}

void alu_mov_reg_lit(struct CPU* cpu, int op1_value, int op2_value) {
    int* target_register;
    int value = op2_value;

    switch (op1_value) {
        case 0:
            target_register = &cpu->registers.AYB;
            break;
        case 1:
            target_register = &cpu->registers.BEN;
            break;
        case 2:
            target_register = &cpu->registers.GIM;
            break;
        case 3:
            target_register = &cpu->registers.DA;
            break;
        case 4:
            target_register = &cpu->registers.ECH;
            break;
        case 5:
            target_register = &cpu->registers.ZA;
            break;
        default:
            // Handle invalid op2_value
            return;
    }

    *target_register = value;
}

void alu_mov_reg_mem(struct CPU* cpu, int op1_value, int op2_value) {
    int* target_register;
    int value = cpu->memory[op2_value];

    switch (op1_value) {
        case 0:
            target_register = &cpu->registers.AYB;
            break;
        case 1:
            target_register = &cpu->registers.BEN;
            break;
        case 2:
            target_register = &cpu->registers.GIM;
            break;
        case 3:
            target_register = &cpu->registers.DA;
            break;
        case 4:
            target_register = &cpu->registers.ECH;
            break;
        case 5:
            target_register = &cpu->registers.ZA;
            break;
        default:
            // Handle invalid op2_value
            return;
    }

    *target_register = value;
}

void alu_mov_reg_reg(struct CPU* cpu, int op1_value, int op2_value) {
    int* target_register;
    int value;

    switch (op2_value) {
        case 0:
            value = cpu->registers.AYB;
            break;
        case 1:
            value = cpu->registers.BEN;
            break;
        case 2:
            value = cpu->registers.GIM;
            break;
        case 3:
            value = cpu->registers.DA;
            break;
        case 4:
            value = cpu->registers.ECH;
            break;
        case 5:
            value = cpu->registers.ZA;
            break;
        default:
            // Handle invalid op1_value
            return;
    }

    switch (op1_value) {
        case 0:
            target_register = &cpu->registers.AYB;
            break;
        case 1:
            target_register = &cpu->registers.BEN;
            break;
        case 2:
            target_register = &cpu->registers.GIM;
            break;
        case 3:
            target_register = &cpu->registers.DA;
            break;
        case 4:
            target_register = &cpu->registers.ECH;
            break;
        case 5:
            target_register = &cpu->registers.ZA;
            break;
        default:
            // Handle invalid op2_value
            return;
    }

    *target_register = value;
}
