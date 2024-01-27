#include "alu.h"
#include "cpu.h"

#include <stdio.h>
#include <limits.h>

enum Operand { AYB, BEN, GIM, DA, ECH, ZA};

void alu_initialize(struct ALU* alu, struct CPU* parent_cpu) {
    alu->parent_cpu = parent_cpu;
}

int alu_jmp(struct CPU* cpu, int op1_value, int op1_category) {
    int i = 0;
    while(i != op1_value) {
        ++i;
    }

    return i;
}

void set_cpu_flag(struct CPU* cpu, int value) {
    // Clear all bits initially
    cpu->cpu_flag = 0;
    // Sign flag
    if (value < 0) {
        cpu->cpu_flag |= (1 << 0);
    }

    // Zero flag
    if (value == 0) {
        cpu->cpu_flag |= (1 << 1);
    }

    // Overflow flag
    if (value > INT_MAX || value < INT_MIN) {
        cpu->cpu_flag |= (1 << 2);
    }
}

void alu_cmp(struct CPU* cpu, int op1_value, int op1_category, int op2_value, int op2_category) {
    if(op1_category == 3 && op2_category == 3) {
        alu_cmp_reg_reg(cpu, op1_value, op2_value);
    } else if(op1_category == 3 && op2_category == 0) {
        alu_cmp_reg_mem(cpu, op1_value, op2_value);
    } else if(op1_category == 3 && op2_category == 2) {
        alu_cmp_reg_lit(cpu, op1_value, op2_value);
    } else if(op1_category == 0 && op2_category == 3) {
        alu_cmp_mem_reg(cpu, op1_value, op2_value);
    } else if(op1_category == 0 && op2_category == 0) {
        alu_cmp_mem_mem(cpu, op1_value, op2_value);
    } else if(op1_category  == 0 && op2_category == 2) {
        alu_cmp_mem_lit(cpu, op1_value, op2_value);
    } else {
        // Handle Invalid Operands
    }
}

void alu_cmp_reg_reg(struct CPU* cpu, int op1_value, int op2_value) {
    int value1;
    int value2;

    switch (op1_value) {
        case 0:
            value1 = cpu->registers.AYB;
            break;
        case 1:
            value1 = cpu->registers.BEN;
            break;
        case 2:
            value1 = cpu->registers.GIM;
            break;
        case 3:
            value1 = cpu->registers.DA;
            break;
        case 4:
            value1 = cpu->registers.ECH;
            break;
        case 5:
            value1 = cpu->registers.ZA;
            break;
        default:
            // Handle invalid op1_value
            return;
    }

    switch (op2_value) {
        case 0:
            value2 = cpu->registers.AYB;
            break;
        case 1:
            value2 = cpu->registers.BEN;
            break;
        case 2:
            value2 = cpu->registers.GIM;
            break;
        case 3:
            value2 = cpu->registers.DA;
            break;
        case 4:
            value2 = cpu->registers.ECH;
            break;
        case 5:
            value2 = cpu->registers.ZA;
            break;
        default:
            // Handle invalid op2_value
            return;
    }

    set_cpu_flag(cpu, value1 - value2);
}

void alu_cmp_reg_mem(struct CPU* cpu, int op1_value, int op2_value) {
    int value1;
    int value2 = cpu->memory[op2_value];

    switch (op1_value) {
        case 0:
            value1 = cpu->registers.AYB;
            break;
        case 1:
            value1 = cpu->registers.BEN;
            break;
        case 2:
            value1 = cpu->registers.GIM;
            break;
        case 3:
            value1 = cpu->registers.DA;
            break;
        case 4:
            value1 = cpu->registers.ECH;
            break;
        case 5:
            value1 = cpu->registers.ZA;
            break;
        default:
            // Handle invalid op2_value
            return;
    }

    set_cpu_flag(cpu, value1 - value2);
}

void alu_cmp_reg_lit(struct CPU* cpu, int op1_value, int op2_value) {
    int value1;
    int value2 = op2_value;

    switch (op1_value) {
        case 0:
            value2 = cpu->registers.AYB;
            break;
        case 1:
            value2 = cpu->registers.BEN;
            break;
        case 2:
            value2 = cpu->registers.GIM;
            break;
        case 3:
            value2 = cpu->registers.DA;
            break;
        case 4:
            value2 = cpu->registers.ECH;
            break;
        case 5:
            value2 = cpu->registers.ZA;
            break;
        default:
            // Handle invalid op2_value
            return;
    }

    set_cpu_flag(cpu, value1 - value2);
}

void alu_cmp_mem_reg(struct CPU* cpu, int op1_value, int op2_value) {
    int value1 = cpu->memory[op1_value];
    int value2 = 0;

    switch (op2_value) {
        case 0:
            value2 = cpu->registers.AYB;
            break;
        case 1:
            value2 = cpu->registers.BEN;
            break;
        case 2:
            value2 = cpu->registers.GIM;
            break;
        case 3:
            value2 = cpu->registers.DA;
            break;
        case 4:
            value2 = cpu->registers.ECH;
            break;
        case 5:
            value2 = cpu->registers.ZA;
            break;
        default:
            // Handle invalid op1_value
            return;
    }

    set_cpu_flag(cpu, value1 - value2);
}

void alu_cmp_mem_mem(struct CPU* cpu, int op1_value, int op2_value) {
    set_cpu_flag(cpu, cpu->memory[op1_value] - cpu->memory[op2_value]);
}

void alu_cmp_mem_lit(struct CPU* cpu, int op1_value, int op2_value) {
    set_cpu_flag(cpu, cpu->memory[op1_value] - op2_value);
}

void alu_not(struct CPU* cpu, int op1_value, int op1_category) {
    if(op1_category == 3) {
        switch (op1_value) {
            case 0:
                cpu->registers.AYB = ~cpu->registers.AYB;
                break;
            case 1:
                cpu->registers.BEN = ~cpu->registers.BEN;
                break;
            case 2:
                cpu->registers.GIM = ~cpu->registers.GIM;
                break;
            case 3:
                cpu->registers.DA = ~cpu->registers.DA;
                break;
            case 4:
                cpu->registers.ECH = ~cpu->registers.ECH;
                break;
            case 5:
                cpu->registers.ZA = ~cpu->registers.ZA;
                break;
            default:
                // Handle invalid op2_value
                return;
        }
    } else if(op1_category == 0) {
        cpu->memory[op1_value] = !cpu->memory[op1_value];
    } else {
        // Handle invalid op1
    }
}

void alu_or(struct CPU* cpu, int op1_value, int op1_category, int op2_value, int op2_category) {
    if(op1_category == 3 && op2_category == 3) {
        alu_or_reg_reg(cpu, op1_value, op2_value);
    } else if(op1_category == 3 && op2_category == 0) {
        alu_or_reg_mem(cpu, op1_value, op2_value);
    } else if(op1_category == 3 && op2_category == 2) {
        alu_or_reg_lit(cpu, op1_value, op2_value);
    } else if(op1_category == 0 && op2_category == 3) {
        alu_or_mem_reg(cpu, op1_value, op2_value);
    } else if(op1_category == 0 && op2_category == 0) {
        alu_or_mem_mem(cpu, op1_value, op2_value);
    } else if(op1_category  == 0 && op2_category == 2) {
        alu_or_mem_lit(cpu, op1_value, op2_value);
    } else {
        // Handle Invalid Operands
    }
}

void alu_or_reg_reg(struct CPU* cpu, int op1_value, int op2_value) {
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

    *target_register |= value;

    set_cpu_flag(cpu, *target_register);
}

void alu_or_reg_mem(struct CPU* cpu, int op1_value, int op2_value) {
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

    *target_register |= value;

    set_cpu_flag(cpu, *target_register);
}

void alu_or_reg_lit(struct CPU* cpu, int op1_value, int op2_value) {
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

    *target_register |= value;

    set_cpu_flag(cpu, *target_register);
}

void alu_or_mem_reg(struct CPU* cpu, int op1_value, int op2_value) {
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

    cpu->memory[op1_value] |= value;

    set_cpu_flag(cpu, cpu->memory[op1_value]);
}

void alu_or_mem_mem(struct CPU* cpu, int op1_value, int op2_value) {
    cpu->memory[op1_value] |= cpu->memory[op2_value];

    set_cpu_flag(cpu, cpu->memory[op1_value]);
}

void alu_or_mem_lit(struct CPU* cpu, int op1_value, int op2_value) {
    cpu->memory[op1_value] |= op2_value;

    set_cpu_flag(cpu, cpu->memory[op1_value]);
}

void alu_and(struct CPU* cpu, int op1_value, int op1_category, int op2_value, int op2_category) {
    if(op1_category == 3 && op2_category == 3) {
        alu_and_reg_reg(cpu, op1_value, op2_value);
    } else if(op1_category == 3 && op2_category == 0) {
        alu_and_reg_mem(cpu, op1_value, op2_value);
    } else if(op1_category == 3 && op2_category == 2) {
        alu_and_reg_lit(cpu, op1_value, op2_value);
    } else if(op1_category == 0 && op2_category == 3) {
        alu_and_mem_reg(cpu, op1_value, op2_value);
    } else if(op1_category == 0 && op2_category == 0) {
        alu_and_mem_mem(cpu, op1_value, op2_value);
    } else if(op1_category  == 0 && op2_category == 2) {
        alu_and_mem_lit(cpu, op1_value, op2_value);
    } else {
        // Handle Invalid Operands
    }
}

void alu_and_reg_reg(struct CPU* cpu, int op1_value, int op2_value) {
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

    *target_register &= value;

    set_cpu_flag(cpu, *target_register);
}

void alu_and_reg_mem(struct CPU* cpu, int op1_value, int op2_value) {
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

    *target_register &= value;

    set_cpu_flag(cpu, *target_register);
}

void alu_and_reg_lit(struct CPU* cpu, int op1_value, int op2_value) {
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

    *target_register &= value;

    set_cpu_flag(cpu, *target_register);
}

void alu_and_mem_reg(struct CPU* cpu, int op1_value, int op2_value) {
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

    cpu->memory[op1_value] &= value;

    set_cpu_flag(cpu, cpu->memory[op1_value]);
}

void alu_and_mem_mem(struct CPU* cpu, int op1_value, int op2_value) {
    cpu->memory[op1_value] &= cpu->memory[op2_value];

    set_cpu_flag(cpu, cpu->memory[op1_value]);
}

void alu_and_mem_lit(struct CPU* cpu, int op1_value, int op2_value) {
    cpu->memory[op1_value] &= op2_value;

    set_cpu_flag(cpu, cpu->memory[op1_value]);
}

void alu_div(struct CPU* cpu, int op1_value, int op1_category, int op2_value, int op2_category) {
    if(op1_category == 3 && op2_category == 3) {
        alu_div_reg_reg(cpu, op1_value, op2_value);
    } else if(op1_category == 3 && op2_category == 0) {
        alu_div_reg_mem(cpu, op1_value, op2_value);
    } else if(op1_category == 3 && op2_category == 2) {
        alu_div_reg_lit(cpu, op1_value, op2_value);
    } else if(op1_category == 0 && op2_category == 3) {
        alu_div_mem_reg(cpu, op1_value, op2_value);
    } else if(op1_category == 0 && op2_category == 0) {
        alu_div_mem_mem(cpu, op1_value, op2_value);
    } else if(op1_category  == 0 && op2_category == 2) {
        alu_div_mem_lit(cpu, op1_value, op2_value);
    } else {
        // Handle Invalid Operands
    }
}

void alu_div_reg_reg(struct CPU* cpu, int op1_value, int op2_value) {
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

    if(value == 0) {
        return;
    }

    *target_register /= value;

    set_cpu_flag(cpu, *target_register);
}

void alu_div_reg_mem(struct CPU* cpu, int op1_value, int op2_value) {
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

    if(value == 0) {
        return;
    }

    *target_register /= value;

    set_cpu_flag(cpu, *target_register);
}

void alu_div_reg_lit(struct CPU* cpu, int op1_value, int op2_value) {
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

    if(value == 0) {
        return;
    }

    *target_register /= value;

    set_cpu_flag(cpu, *target_register);
}

void alu_div_mem_reg(struct CPU* cpu, int op1_value, int op2_value) {
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

    if(value == 0) {
        return;
    }

    cpu->memory[op1_value] /= value;

    set_cpu_flag(cpu, cpu->memory[op1_value]);
}

void alu_div_mem_mem(struct CPU* cpu, int op1_value, int op2_value) {
    if(cpu->memory[op2_value] == 0) {
        return;
    }

    cpu->memory[op1_value] /= cpu->memory[op2_value];

    set_cpu_flag(cpu, cpu->memory[op1_value]);
}

void alu_div_mem_lit(struct CPU* cpu, int op1_value, int op2_value) {
    if(op2_value == 0) {
        return;
    }

    cpu->memory[op1_value] /= op2_value;

    set_cpu_flag(cpu, cpu->memory[op1_value]);
}

void alu_mul(struct CPU* cpu, int op1_value, int op1_category, int op2_value, int op2_category) {
    if(op1_category == 3 && op2_category == 3) {
        alu_mul_reg_reg(cpu, op1_value, op2_value);
    } else if(op1_category == 3 && op2_category == 0) {
        alu_mul_reg_mem(cpu, op1_value, op2_value);
    } else if(op1_category == 3 && op2_category == 2) {
        alu_mul_reg_lit(cpu, op1_value, op2_value);
    } else if(op1_category == 0 && op2_category == 3) {
        alu_mul_mem_reg(cpu, op1_value, op2_value);
    } else if(op1_category == 0 && op2_category == 0) {
        alu_mul_mem_mem(cpu, op1_value, op2_value);
    } else if(op1_category  == 0 && op2_category == 2) {
        alu_mul_mem_lit(cpu, op1_value, op2_value);
    } else {
        // Handle Invalid Operands
    }
}

void alu_mul_reg_reg(struct CPU* cpu, int op1_value, int op2_value) {
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

    *target_register *= value;

    set_cpu_flag(cpu, *target_register);
}

void alu_mul_reg_mem(struct CPU* cpu, int op1_value, int op2_value) {
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

    *target_register *= value;

    set_cpu_flag(cpu, *target_register);
}

void alu_mul_reg_lit(struct CPU* cpu, int op1_value, int op2_value) {
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

    *target_register *= value;

    set_cpu_flag(cpu, *target_register);
}

void alu_mul_mem_reg(struct CPU* cpu, int op1_value, int op2_value) {
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

    cpu->memory[op1_value] *= value;

    set_cpu_flag(cpu, cpu->memory[op1_value]);
}

void alu_mul_mem_mem(struct CPU* cpu, int op1_value, int op2_value) {
    cpu->memory[op1_value] *= cpu->memory[op2_value];

    set_cpu_flag(cpu, cpu->memory[op1_value]);
}

void alu_mul_mem_lit(struct CPU* cpu, int op1_value, int op2_value) {
    cpu->memory[op1_value] *= op2_value;

    set_cpu_flag(cpu, cpu->memory[op1_value]);
}

void alu_sub(struct CPU* cpu, int op1_value, int op1_category, int op2_value, int op2_category) {
    if(op1_category == 3 && op2_category == 3) {
        alu_sub_reg_reg(cpu, op1_value, op2_value);
    } else if(op1_category == 3 && op2_category == 0) {
        alu_sub_reg_mem(cpu, op1_value, op2_value);
    } else if(op1_category == 3 && op2_category == 2) {
        alu_sub_reg_lit(cpu, op1_value, op2_value);
    } else if(op1_category == 0 && op2_category == 3) {
        alu_sub_mem_reg(cpu, op1_value, op2_value);
    } else if(op1_category == 0 && op2_category == 0) {
        alu_sub_mem_mem(cpu, op1_value, op2_value);
    } else if(op1_category  == 0 && op2_category == 2) {
        alu_sub_mem_lit(cpu, op1_value, op2_value);
    } else {
        // Handle Invalid Operands
    }
}

void alu_sub_reg_reg(struct CPU* cpu, int op1_value, int op2_value) {
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

    *target_register -= value;

    set_cpu_flag(cpu, *target_register);
}

void alu_sub_reg_mem(struct CPU* cpu, int op1_value, int op2_value) {
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

    *target_register -= value;

    set_cpu_flag(cpu, *target_register);
}

void alu_sub_reg_lit(struct CPU* cpu, int op1_value, int op2_value) {
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

    *target_register -= value;

    set_cpu_flag(cpu, *target_register);
}

void alu_sub_mem_reg(struct CPU* cpu, int op1_value, int op2_value) {
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

    cpu->memory[op1_value] -= value;

    set_cpu_flag(cpu, cpu->memory[op1_value]);
}

void alu_sub_mem_mem(struct CPU* cpu, int op1_value, int op2_value) {
    cpu->memory[op1_value] -= cpu->memory[op2_value];

    set_cpu_flag(cpu, cpu->memory[op1_value]);
}

void alu_sub_mem_lit(struct CPU* cpu, int op1_value, int op2_value) {
    cpu->memory[op1_value] -= op2_value;

    set_cpu_flag(cpu, cpu->memory[op1_value]);
}

void alu_add(struct CPU* cpu, int op1_value, int op1_category, int op2_value, int op2_category) {
    if(op1_category == 3 && op2_category == 3) {
        alu_add_reg_reg(cpu, op1_value, op2_value);
    } else if(op1_category == 3 && op2_category == 0) {
        alu_add_reg_mem(cpu, op1_value, op2_value);
    } else if(op1_category == 3 && op2_category == 2) {
        alu_add_reg_lit(cpu, op1_value, op2_value);
    } else if(op1_category == 0 && op2_category == 3) {
        alu_add_mem_reg(cpu, op1_value, op2_value);
    } else if(op1_category == 0 && op2_category == 0) {
        alu_add_mem_mem(cpu, op1_value, op2_value);
    } else if(op1_category  == 0 && op2_category == 2) {
        alu_add_mem_lit(cpu, op1_value, op2_value);
    } else {
        // Handle Invalid Operands
    }
}

void alu_add_reg_reg(struct CPU* cpu, int op1_value, int op2_value) {
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

    *target_register += value;

    set_cpu_flag(cpu, *target_register);
}

void alu_add_reg_mem(struct CPU* cpu, int op1_value, int op2_value) {
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

    *target_register += value;

    set_cpu_flag(cpu, *target_register);
}

void alu_add_reg_lit(struct CPU* cpu, int op1_value, int op2_value) {
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

    *target_register += value;

    set_cpu_flag(cpu, *target_register);
}

void alu_add_mem_reg(struct CPU* cpu, int op1_value, int op2_value) {
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

    cpu->memory[op1_value] += value;

    set_cpu_flag(cpu, cpu->memory[op1_value]);
}

void alu_add_mem_mem(struct CPU* cpu, int op1_value, int op2_value) {
    cpu->memory[op1_value] += cpu->memory[op2_value];

    set_cpu_flag(cpu, cpu->memory[op1_value]);
}

void alu_add_mem_lit(struct CPU* cpu, int op1_value, int op2_value) {
    cpu->memory[op1_value] += op2_value;

    set_cpu_flag(cpu, cpu->memory[op1_value]);
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
