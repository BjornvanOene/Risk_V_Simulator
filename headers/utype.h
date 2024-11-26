#ifndef UTYPEH
#define UTYPEH
#include <stdint.h>
#include "regs.h"

typedef struct {
    uint32_t op;
    int32_t imm;
    uint32_t rd;
} utype;

utype* udecode(unsigned int, CPURegs*);
void lui(utype*,CPURegs*);

#endif