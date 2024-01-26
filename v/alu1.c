#include "alu.h"
#include "cpu.h"
#include <stdio.h>



void alu_mov(struct CPU* cpu, const char* op1, const char* op2) {
    if (cpu_is_register(cpu, op2)) {
        cpu_set_register(cpu, op1, cpu_get_register(cpu, op2));
    } else {
        cpu_set_register(cpu, op1, atoi(op2));
    }
}

void alu_add(struct CPU* cpu, const char* op1, const char* op2) {
    if (cpu_is_register(cpu, op2)) {
        int tmp = cpu_get_register(cpu, op1) + cpu_get_register(cpu, op2);
        cpu_set_register(cpu, op1, tmp);
    } else {
        int res = cpu_get_register(cpu, op1) + atoi(op2);
        cpu_set_register(cpu, op1, res);
    }
}

void alu_sub(struct CPU* cpu, const char* op1, const char* op2) {
    if (cpu_is_register(cpu, op2)) {
        int tmp = cpu_get_register(cpu, op1) - cpu_get_register(cpu, op2);
        cpu_set_register(cpu, op1, tmp);
    } else {
        int res = cpu_get_register(cpu, op1) - atoi(op2);
        cpu_set_register(cpu, op1, res);
    }
}

void alu_mul(struct CPU* cpu, const char* op1, const char* op2) {
    if (cpu_is_register(cpu, op2)) {
        int tmp = cpu_get_register(cpu, op1) * cpu_get_register(cpu, op2);
        cpu_set_register(cpu, op1, tmp);
    } else {
        int res = cpu_get_register(cpu, op1) * atoi(op2);
        cpu_set_register(cpu, op1, res);
    }
}

void alu_div(struct CPU* cpu, const char* op1, const char* op2) {
    if (cpu_is_register(cpu, op2)) {
        int tmp = cpu_get_register(cpu, op1) / cpu_get_register(cpu, op2);
        cpu_set_register(cpu, op1, tmp);
    } else {
        int res = cpu_get_register(cpu, op1) / atoi(op2);
        cpu_set_register(cpu, op1, res);
    }
}

void alu_and(struct CPU* cpu, const char* op1, const char* op2) {
    if (cpu_is_register(cpu, op2)) {
        int tmp = cpu_get_register(cpu, op1) & cpu_get_register(cpu, op2);
        cpu_set_register(cpu, op1, tmp);
    } else {
        int res = cpu_get_register(cpu, op1) & atoi(op2);
        cpu_set_register(cpu, op1, res);
    }
}

void alu_or(struct CPU* cpu, const char* op1, const char* op2) {
    if (cpu_is_register(cpu, op2)) {
        int tmp = cpu_get_register(cpu, op1) | cpu_get_register(cpu, op2);
        cpu_set_register(cpu, op1, tmp);
    } else {
        int res = cpu_get_register(cpu, op1) | atoi(op2);
        cpu_set_register(cpu, op1, res);
    }
}

void alu_not(struct CPU* cpu, const char* op) {
    int tmp = ~(cpu_get_register(cpu, op));
    cpu_set_register(cpu, op, tmp);
}

void alu_inc(struct CPU* cpu, const char* op) {
    int tmp = cpu_get_register(cpu, op);
    cpu_set_register(cpu, op, ++tmp);
}

void alu_dec(struct CPU* cpu, const char* op) {
    int tmp = cpu_get_register(cpu, op);
    cpu_set_register(cpu, op, --tmp);
}

void alu_cmp(struct CPU* cpu, const char* op1, const char* op2) {
    int tmp1 = cpu_get_register(cpu, op1);
    int tmp2;
    if (cpu_is_register(cpu, op2)) {
        tmp2 = cpu_get_register(cpu, op2);
    } else {
        tmp2 = atoi(op2);
    }
    cpu->cmp_flag = tmp1 - tmp2;
}

void alu_jmp(struct CPU* cpu, const char* label) {
    int jump_address = cpu_get_label(cpu, label);
    if (jump_address != -1) {
        cpu_set_ip(cpu, --jump_address);
    }
}

void alu_jg(struct CPU* cpu, const char* label) {
    if (cpu_get_cmp_flag(cpu) > 0) {
        int jump_address = cpu_get_label(cpu, label);
        if (jump_address != -1) {
            cpu_set_ip(cpu, --jump_address);
        }
    }
}

void alu_jl(struct CPU* cpu, const char* label) {
    if (cpu_get_cmp_flag(cpu) < 0) {
        int jump_address = cpu_get_label(cpu, label);
        if (jump_address != -1) {
            cpu_set_ip(cpu, --jump_address);
        }
    }
}

void alu_je(struct CPU* cpu, const char* label) {
    if (cpu_get_cmp_flag(cpu) == 0) {
        int jump_address = cpu_get_label(cpu, label);
        if (jump_address != -1) {
            cpu_set_ip(cpu, --jump_address);
        }
    }
}

void alu_jge(struct CPU* cpu, const char* label) {
    if (cpu_get_cmp_flag(cpu) >= 0) {
        int jump_address = cpu_get_label(cpu, label);
        if (jump_address != -1) {
            cpu_set_ip(cpu, --jump_address);
        }
    }
}

void alu_jle(struct CPU* cpu, const char* label) {
    if (cpu_get_cmp_flag(cpu) <= 0) {
        int jump_address = cpu_get_label(cpu, label);
        if (jump_address != -1) {
            cpu_set_ip(cpu, --jump_address);
        }
    }
}

void alu_print(struct CPU* cpu, const char* reg) {
    printf("%s : %d\n", reg, cpu_get_register(cpu, reg));
}
