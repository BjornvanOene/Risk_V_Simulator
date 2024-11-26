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
void ifnc3decode(itype*, CPURegs* );
void addi(itype* , CPURegs* );
void andi(itype* , CPURegs* );
void ori(itype* , CPURegs* );
void sltiu(itype* , CPURegs* );
void slti(itype* , CPURegs* );
void srai(itype* , CPURegs* );
void srli(itype* , CPURegs* );
void slli(itype* , CPURegs* );
void xori(itype* , CPURegs* );
#endif