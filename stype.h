#ifndef STYPEH
#define STYPEH

#include <stdint.h>
#include "regs.h"

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
void lb(stype*, CPURegs*, uint8_t*);
void lh(stype*, CPURegs*, uint8_t*);
void lhu(stype* , CPURegs* , uint8_t* );
void lbu(stype* , CPURegs* , uint8_t* );
void sw(stype*, CPURegs*, uint8_t*);
void sb(stype* , CPURegs* , uint8_t* );
void sh(stype* , CPURegs* , uint8_t* );
void storefncs(stype* , CPURegs* , uint8_t* );
void loadfncs(stype* , CPURegs* , uint8_t* );
#endif