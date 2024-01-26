#include "alu.h"

void alu_initialize(struct ALU* alu, struct CPU* parent_cpu) {
    alu->parent_cpu = parent_cpu;
}