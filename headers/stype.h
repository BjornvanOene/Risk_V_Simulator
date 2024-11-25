#ifndef STYPEH
#define STYPEH

#include <stdint.h>
#include <regs.h>

typedef struct {
    uint32_t op;
    int32_t rs1;
    int32_t rs2;
    int32_t imm;
    int32_t fnc3;
    int32_t rd;
} stype;

stype* sdecode(unsigned int, CPURegs*);

void sfnc3decode(stype*, CPURegs*, uint8_t*);
void lw(stype*, CPURegs*, uint8_t*);
void sw(stype*, CPURegs*, uint8_t*);

#endif