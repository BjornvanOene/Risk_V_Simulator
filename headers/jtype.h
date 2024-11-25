#ifndef JTYPEH
#define JTYPEH

#include <stdint.h>
#include "regs.h"

typedef struct{
    uint32_t op;
    uint32_t rd;
    uint32_t imm;
    uint32_t rs1;
    int32_t fnc3;
} jtype;

int32_t signextend12(int32_t val);
void jfnc3decode(jtype* , CPURegs* , uint32_t* );
void jalr(jtype* , CPURegs* , uint32_t* );
void jal(jtype* , CPURegs* , uint32_t* );
#endif