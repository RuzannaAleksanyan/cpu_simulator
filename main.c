#include "cpu.h"

int main() {
    struct CPU my_cpu;
    cpu_initialize(&my_cpu);
    
    int address = cpu_load_from_file(&my_cpu, "code.txt");

    cpu_execute(&my_cpu, address);

    dump_memory(&my_cpu);

    return 0;
}