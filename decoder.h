#ifndef DECODERH
#define DECODERH

#include <stdint.h>
#include <stdlib.h>
#include "regs.h"
#include "itype.h"
#include "jtype.h"

int compCode(uint32_t* instr, CPURegs* regs, uint32_t* pc, uint8_t* sp);
int ecall(uint32_t instr, CPURegs* reg);

#endif