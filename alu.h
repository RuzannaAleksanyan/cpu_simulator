#ifndef _ALU
#define _ALU

struct ALU {
    struct CPU* parent_cpu;
};

void alu_initialize(struct ALU* alu, struct CPU* parent_cpu);
// void alu_mov(struct CPU* cpu, const char* op1, const char* op2);
// void alu_add(struct CPU* cpu, const char* op1, const char* op2);
// void alu_sub(struct CPU* cpu, const char* op1, const char* op2);
// void alu_mul(struct CPU* cpu, const char* op1, const char* op2);
// void alu_div(struct CPU* cpu, const char* op1, const char* op2);
// void alu_and(struct CPU* cpu, const char* op1, const char* op2);
// void alu_or(struct CPU* cpu, const char* op1, const char* op2);
// void alu_not(struct CPU* cpu, const char* op);
// void alu_inc(struct CPU* cpu, const char* op);
// void alu_dec(struct CPU* cpu, const char* op);
// void alu_cmp(struct CPU* cpu, const char* op1, const char* op2);
// void alu_jmp(struct CPU* cpu, const char* label);
// void alu_jg(struct CPU* cpu, const char* label);
// void alu_jl(struct CPU* cpu, const char* label);
// void alu_je(struct CPU* cpu, const char* label);
// void alu_jge(struct CPU* cpu, const char* label);
// void alu_jle(struct CPU* cpu, const char* label);
// void alu_print(struct CPU* cpu, const char* reg);

#endif  // _ALU