void cpu_execute(struct CPU* cpu) {
    while (cpu->ip >= 0 && cpu->ip < MAX_MEMORY_SIZE) {
        char* instruction[3];
        for (int j = 0; j < 3; ++j) {
            instruction[j] = cpu->memory[cpu->ip][j];
        }
        char* opcode = instruction[0];

        if (cpu->instruction_set[opcode]) {
            char* op1 = instruction[1];
            char* op2 = instruction[2];
            cpu->instruction_set[opcode](cpu, op1, op2);
        } else {
            fprintf(stderr, "Invalid instruction: %s\n", opcode);
            break;
        }

        // check if a jump instruction was executed
        if (cpu->ip == cpu_get_ip(cpu)) {
            // no jump occurred, increment the instruction pointer
            cpu_set_ip(cpu, cpu->ip + 1);
        }
    }
}
