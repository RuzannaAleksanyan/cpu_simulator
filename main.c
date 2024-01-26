#include "cpu.h"

int main() {
    struct CPU my_cpu;
    cpu_initialize(&my_cpu);

    // cpu_print_labels(&my_cpu);
    
    int address = cpu_load_from_file(&my_cpu, "code.txt");

    cpu_print_memory(&my_cpu);
    cpu_execute(&my_cpu, address);
    cpu_print_registers(&my_cpu);

    // cpu_print_registers(&my_cpu);

    return 0;
}