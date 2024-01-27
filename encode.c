#include "cpu.h"

enum Instruction { MOV, ADD, SUB, MUL, DIV, AND, OR, NOT, CMP, JMP, JG, JL, JE, PRINT };
enum Operand { AYB, BEN, GIM, DA, ECH, ZA};

int encode(struct CPU* cpu, const char* instruction, const char* op1, const char* op2, int address) {
    
    int val_inst = encode_instruction(cpu, instruction, address);
    int val_op1 = encode_op1(cpu, op1, address);
    int val_op2 = 0;
    if(strcmp(op2, "") != 0) {
        val_op2 = encode_op2(cpu, op2, address);
    }

    if(val_inst && val_op1 && val_op2 && (strcmp(op2, "") != 0)) {
        return 1;
    }
    
    if(strcmp(op2, "") == 0) {
        if(encode_instruction(cpu, instruction, address) && encode_op1(cpu, op1, address)) {
            cpu->memory[address] = (cpu->memory[address] << 6) + 1;
            return 1;
        }
    }

    return 0;
}

int encode_instruction(struct CPU* cpu, const char* instruction, int address) {
    if(strcmp(instruction, "MOV") == 0) {
        cpu->memory[address] = MOV;
    } else if(strcmp(instruction, "ADD") == 0) {
        cpu->memory[address] = ADD;
    } else if(strcmp(instruction, "SUB") == 0) {
        cpu->memory[address] = SUB;
    } else if(strcmp(instruction, "MUL") == 0) {
        cpu->memory[address] = MUL;
    } else if(strcmp(instruction, "DIV") == 0) {
        cpu->memory[address] = DIV;
    } else if(strcmp(instruction, "AND") == 0) {
        cpu->memory[address] = AND;
    } else if(strcmp(instruction, "OR") == 0) {
        cpu->memory[address] = OR;
    } else if(strcmp(instruction, "NOT") == 0) {
        cpu->memory[address] = NOT;
    } else if(strcmp(instruction, "CMP") == 0) {
        cpu->memory[address] = CMP;
    } else if(strcmp(instruction, "JMP") == 0) {
        cpu->memory[address] = JMP;
    } else if(strcmp(instruction, "JG") == 0) {
        cpu->memory[address] = JG;
    } else if(strcmp(instruction, "JL") == 0) {
        cpu->memory[address] = JL;
    } else if(strcmp(instruction, "JE") == 0) {
        cpu->memory[address] = JE;
    } else if(strcmp(instruction, "PRINT") == 0) {
        cpu->memory[address] = PRINT;
    }  else {
        printf("error: Invalid Instruction!");
        return 0;
    }

    return 1;
}

int encode_op1(struct CPU* cpu, const char* op1, int address) {
    if(strcmp(op1, "AYB") == 0) {
        cpu->memory[address] = (cpu->memory[address] << 6) + ((AYB << 2) + 3);
    } else if(strcmp(op1, "BEN") == 0) {
        cpu->memory[address] = (cpu->memory[address] << 6) + ((BEN << 2) + 3);
    } else if(strcmp(op1, "GIM") == 0) {
        cpu->memory[address] = (cpu->memory[address] << 6) + ((GIM << 2) + 3);
    } else if(strcmp(op1, "DA") == 0) {
        cpu->memory[address] = (cpu->memory[address] << 6) + ((DA << 2) + 3);
    } else if(strcmp(op1, "ECH") == 0) {
        cpu->memory[address] = (cpu->memory[address] << 6) + ((ECH << 2) + 3);
    } else if(strcmp(op1, "ZA") == 0) {
        cpu->memory[address] = (cpu->memory[address] << 6) + ((ZA << 2) + 3);
    } else {
        if(op1[0] == '[' && op1[strlen(op1) - 1] == ']') {
            int memory_address = remove_brackets_and_replace_with_number(op1);
            if(memory_address <= address) {
                printf("error: Invalid Memory Address");
                return 0;
            } else {
                cpu->memory[address] = (cpu->memory[address] << 6) + ((memory_address << 2) + 0);
            }
        } else {
            int flag = 0;
            int i = 0;
            while(cpu->labels[i] != NULL) {
                // op1 == cpu->labels[i]
                if(strcmp(op1, cpu->labels[i]) == 0) {
                    // printf("1");
                    flag = 1;
                    cpu->memory[address] = (cpu->memory[address] << 6) + ((i << 2) + 2);
                    break;
                }
                ++i;
            }

            if(!flag) {
                printf("error: Invalid Operand\n");
                return 0;
            }
            
        }
    }

    return 1;
}

int convert_string_to_int(const char* str) {
    const char* res = str;
    if (str[0] == '-') {
        res = str + 1;
    }
    int result = atoi(res);

    // If the original string was negative, make the result negative
    if (str[0] == '-') {
        result = 0 - result;
    }

    return result;
}


int encode_op2(struct CPU* cpu, const char* op2, int address) {
    if(strcmp(op2, "AYB") == 0) {
        cpu->memory[address] = (cpu->memory[address] << 6) + ((AYB << 2) + 3);
    } else if(strcmp(op2, "BEN") == 0) {
        cpu->memory[address] = (cpu->memory[address] << 6) + ((BEN << 2) + 3);
    } else if(strcmp(op2, "GIM") == 0) {
        cpu->memory[address] = (cpu->memory[address] << 6) + ((GIM << 2) + 3);
    } else if(strcmp(op2, "DA") == 0) {
        cpu->memory[address] = (cpu->memory[address] << 6) + ((DA << 2) + 3);
    } else if(strcmp(op2, "ECH") == 0) {
        cpu->memory[address] = (cpu->memory[address] << 6) + ((ECH << 2) + 3);
    } else if(strcmp(op2, "ZA") == 0) {
        cpu->memory[address] = (cpu->memory[address] << 6) + ((ZA << 2) + 3);
    } else if(op2[0] == '[' && op2[strlen(op2) - 1] == ']') {
        int memory_address = remove_brackets_and_replace_with_number(op2);
        if(memory_address <= address) {
            printf("error: Invalid Memory Address");
            return 0;
        } else {
            cpu->memory[address] = (cpu->memory[address] << 6) + ((memory_address << 2) + 0);
        }
    } else {
        int integer = convert_string_to_int(op2);
        cpu->memory[address] = (cpu->memory[address] << 6) + ((integer << 2) + 2);
    }
    

    return 1;
}