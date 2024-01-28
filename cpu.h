#ifndef _CPU
#define _CPU

#include "registers.h"
#include "alu.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define INSTRUCTION_COUNT 14
#define MEMORY_SIZE 16
#define MAX_SIZE_LABEL 16

struct Label {
    char* name;
    int address;
};

struct CPU {
    struct Register registers;
    struct ALU alu;
    short memory[MEMORY_SIZE];
    struct Label labels[MAX_SIZE_LABEL];
    int cpu_flag;
};

void dump_memory(struct CPU* cpu);

void cpu_initialize(struct CPU* cpu);
void cpu_initialize_memory(struct CPU* cpu);
void cpu_initialize_registers(struct CPU* cpu);
void cpu_initialize_labels(struct CPU* cpu);

int cpu_load_from_file(struct CPU* cpu, const char* file_name);

void cpu_execute(struct CPU* cpu, int address);

int decode(struct CPU* cpu, short code);

int remove_brackets_and_replace_with_number(const char* input);
int convert_string_to_int(const char* str);

int cpu_extract_labels(struct CPU* cpu, const char* file_name);

char* cpu_trim(char* str);
// int cpu_is_one_operand_instruction(const char* instruction);

int encode(struct CPU* cpu, const char* instruction, const char* op1, const char* op2, int address);
int encode_instruction(struct CPU* cpu, const char* instruction, int address);
int encode_op1(struct CPU* cpu, const char* op1, int address);
int encode_op2(struct CPU* cpu, const char* op2, int address);

void cpu_print_memory(const struct CPU* cpu);
void cpu_print_registers(const struct CPU* cpu);
void cpu_print_labels(const struct CPU* cpu);

#endif // _CPU
