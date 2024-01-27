#include "cpu.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* cpu_trim(char* str) {
    char* end;

    while (isspace((unsigned char)*str)) {
        str++;
    }

    if (*str == '\0') {
        return str;
    }

    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) {
        end--;
    }

    *(end + 1) = '\0';

    return str;
}

int cpu_is_one_operand_instruction(const char* instruction) {
    const char* one_operand_instructions[] = { "JMP", "JG", "JL", "JE", "PRINT" };
    int num_instructions = sizeof(one_operand_instructions) / sizeof(one_operand_instructions[0]);

    for (int i = 0; i < num_instructions; ++i) {
        if (strcmp(instruction, one_operand_instructions[i]) == 0) {
            return 1;
        }
    }

    return 0;
}

int remove_brackets_and_replace_with_number(const char* input) {
    int result = 0;

    if (input == NULL || input[0] == '\0') {
        return result;
    }

    size_t length = strlen(input);

    char* modifiable_input = malloc(length);
    if (modifiable_input == NULL) {
        return result;
    }

    strcpy(modifiable_input, input);

    if (length >= 2 && modifiable_input[0] == '[' && modifiable_input[length - 1] == ']') {
        memmove(modifiable_input, modifiable_input + 1, length - 2);

        modifiable_input[length - 2] = '\0';

        result = atoi(modifiable_input);
    }

    free(modifiable_input);

    return result;
}

int cpu_extract_labels(struct CPU* cpu, const char* file_name) {
    FILE* file = fopen(file_name, "r");
    if (!file) {
        fprintf(stderr, "Failed to open file: %s\n", file_name);
        return 0;
    }

    char line[256];
    int label_count = 0;
    int address = 0;

    while (fgets(line, sizeof(line), file)) {
        // remove whitespace
        char* trimmed_line = cpu_trim(line);

        // skip empty lines
        if (strlen(trimmed_line) == 0) {
            continue;
        }

        int length = strlen(trimmed_line);

        if (length > 0 && trimmed_line[length - 1] == ':') {
            trimmed_line[length - 1] = '\0';
            char* label = trimmed_line;

            // Check for duplicate labels
            int duplicate = 0;
            for (int i = 0; i < label_count; ++i) {
                if (cpu->labels[i].name != NULL && strcmp(cpu->labels[i].name, label) == 0) {
                    printf("error: Duplicate label found: %s\n", label);
                    duplicate = 1;
                    break;
                }
            }

            if (!duplicate) {
                // Add the label to the CPU's labels array
                if (label_count < MAX_SIZE_LABEL) {
                    cpu->labels[label_count].name = strdup(label);
                    cpu->labels[label_count].address = address;
                    ++label_count;
                } else {
                    fprintf(stderr, "error: Too many labels, increase MAX_SIZE_LABEL.\n");
                    break;
                }
            }
        }
        ++address;
    }

    fclose(file);
    return 1;
}

void split_instruction(char *instruction, char *part1, char *part2, char *part3) {
    int result = sscanf(instruction, "%s %s %s", part1, part2, part3);

    if (result == 2) {
        strcpy(part3, "");  // Set op3 to an empty string
    }
}

int cpu_load_from_file(struct CPU* cpu, const char* file_name) {
    FILE* file = fopen(file_name, "r");
    if (!file) {
        fprintf(stderr, "Failed to open file: %s\n", file_name);
        return 0;
    }

    char line[256];
    int address = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        char* trimmed_line = cpu_trim(line);

        if (strlen(trimmed_line) == 0) {
            continue;
        }

        int length = strlen(trimmed_line);

        if (trimmed_line[length - 1] == ':') {
            continue;
        } else {
            char* comma_pos = strchr(trimmed_line, ',');
            if (!comma_pos) {
                fprintf(stderr, "Failed to parse line in file: %s\n", file_name);
                break;
            }
            
            char instruction[50], op1[50], op2[50];
            split_instruction(trimmed_line, instruction, op1, op2);

            int length = strlen(op1);
            if (op1[length - 1] == ',') {
                op1[length - 1] = '\0';
            }

            int val = encode(cpu, instruction, op1, op2, address);
            if (!val) {
                return -1;
            }

            ++address;
        }
    }

    fclose(file);
    return address;
}
