#ifndef BTYPEH
#define BTYPEH

#include <stdint.h>
#include "regs.h"

typedef struct{
    uint32_t op;
    uint32_t fnc3;
    uint32_t rs1;
    uint32_t rs2;
    int32_t offset;
} btype;

btype* bdecode(uint32_t, CPURegs*);
void beq(btype*, CPURegs*, uint32_t*);
void bne(btype* , CPURegs* , uint32_t*);
void blt(btype* , CPURegs* , uint32_t*);
void bgeu(btype* , CPURegs* , uint32_t*);
void bltu(btype* , CPURegs* , uint32_t*);
void bge(btype* , CPURegs* , uint32_t*);

#endif