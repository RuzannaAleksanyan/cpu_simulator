#include "registers.h"

void reset_registers(struct Register* registers) {
    registers->AYB = 0;
    registers->BEN = 0;
    registers->GIM = 0;
    registers->DA = 0;
    registers->ECH = 0;
    registers->ZA = 0;
}