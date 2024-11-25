#ifndef REGS
#define REGS

#include <stdint.h>
#include <stdio.h>

typedef struct CPURegs{
    int32_t x[32];
} CPURegs;

CPURegs* init_regs();

#endif