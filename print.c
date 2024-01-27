#include "cpu.h"

void print_binary_16bits(short num) {
    num = num & 0xFFFF;

    for (int i = 15; i >= 0; --i) {
        int bit = (num >> i) & 1;
        printf("%d", bit);
    }
}

void cpu_print_memory(const struct CPU* cpu) {
    printf("Memory:\n");

    for (int i = 0; i < MEMORY_SIZE; ++i) {
        printf("Address %d: ", i);
        print_binary_16bits(cpu->memory[i]);
        printf("\n");
    }

    printf("\n");
}

void cpu_print_registers(const struct CPU* cpu) {
    printf("Registers:\n");
    printf("AYB: %d\n", cpu->registers.AYB);
    printf("BEN: %d\n", cpu->registers.BEN);
    printf("GIM: %d\n", cpu->registers.GIM);
    printf("DA:  %d\n", cpu->registers.DA);
    printf("ECH: %d\n", cpu->registers.ECH);
    printf("ZA:  %d\n", cpu->registers.ZA);
    printf("\n");

    printf("Flags:\n");
    printf("SF: %d\n", (cpu->cpu_flag & (1 << 0)) ? 1 : 0); // Sign Flag
    printf("ZF: %d\n", (cpu->cpu_flag & (1 << 1)) ? 1 : 0); // Zero Flag
    printf("OF: %d\n", (cpu->cpu_flag & (1 << 2)) ? 1 : 0); // Overflow Flag
    printf("DF: %d\n", (cpu->cpu_flag & (1 << 3)) ? 1 : 0); // Placeholder for an additional flag
}

void cpu_print_labels(const struct CPU* cpu) {
    printf("Labels:\n");

    int i = 0;
    while (cpu->labels[i] != NULL) {
        printf("Label %d: %s\n", i, cpu->labels[i]);
        ++i;
    }

    printf("\n");
}