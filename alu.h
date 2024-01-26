#ifndef _ALU
#define _ALU

struct ALU {
    struct CPU* parent_cpu;
};

void alu_initialize(struct ALU* alu, struct CPU* parent_cpu);

void alu_mov(struct CPU* cpu, int op1_value, int op1_category, int op2_value, int op2_category);
void alu_mov_reg_reg(struct CPU* cpu, int op1_value, int op2_value);
void alu_mov_reg_mem(struct CPU* cpu, int op1_value, int op2_value);
void alu_mov_reg_lit(struct CPU* cpu, int op1_value, int op2_value);
void alu_mov_mem_reg(struct CPU* cpu, int op1_value, int op2_value);
void alu_mov_mem_mem(struct CPU* cpu, int op1_value, int op2_value);
void alu_mov_mem_lit(struct CPU* cpu, int op1_value, int op2_value);

// void alu_add(struct CPU* cpu, int op1_value, int op2_value);
// void alu_sub(struct CPU* cpu, int op1_value, int op2_value);
// void alu_mul(struct CPU* cpu, int op1_value, int op2_value);
// void alu_div(struct CPU* cpu, int op1_value, int op2_value);
// void alu_and(struct CPU* cpu, int op1_value, int op2_value);
// void alu_or(struct CPU* cpu, int op1_value, int op2_value);
// void alu_not(struct CPU* cpu, const char* op);
// void alu_cmp(struct CPU* cpu, int op1_value, int op2_value);
// void alu_jmp(struct CPU* cpu, const char* label);
// void alu_jg(struct CPU* cpu, const char* label);
// void alu_jl(struct CPU* cpu, const char* label);
// void alu_je(struct CPU* cpu, const char* label);
// void alu_print(struct CPU* cpu, const char* reg);


#endif  // _ALU