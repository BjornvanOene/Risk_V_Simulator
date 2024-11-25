#ifndef ITYPEH
#define ITYPEH

#include <stdint.h>
#include "regs.h"

typedef struct {
    uint32_t op;
    int32_t imm;
    uint32_t rd;
    uint32_t rs1;
    uint32_t fnc3;
    uint32_t shamt;
    uint32_t shtyp;
} itype;

itype* decodei(uint32_t , CPURegs* );

#endif