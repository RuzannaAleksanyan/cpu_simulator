#include "cpu.h"

void cpu_initialize(struct CPU* cpu) {
    cpu->cpu_flag = 0;
    alu_initialize(&cpu->alu, cpu);

    cpu_initialize_registers(cpu);
    cpu_initialize_labels(cpu);
    cpu_initialize_memory(cpu);

    char* file_name = "code.txt";
    FILE* file = fopen(file_name, "r");
    cpu_extract_labels(cpu, file_name);
}

void cpu_initialize_memory(struct CPU* cpu) {
    for (int i = 0; i < MEMORY_SIZE; ++i) {
        cpu->memory[i] = 0;
    }
}

void cpu_initialize_labels(struct CPU* cpu) {
    for (int i = 0; i < MAX_SIZE_LABEL; ++i) {
        cpu->labels[i].name = NULL; 
        cpu->labels[i].address = -1; 
    }
}

void cpu_initialize_registers(struct CPU* cpu) {
    reset_registers(&cpu->registers);
}