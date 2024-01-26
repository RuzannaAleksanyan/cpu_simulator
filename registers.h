#ifndef REGISTER
#define REGISTER

struct Register {
    int AYB;
    int BEN;
    int GIM;
    int DA;
    int ECH;
    int ZA;
};

void reset_registers(struct Register* registers);

#endif  //REGISTER