#ifndef RTYPEH
#define RTYPEH

#include <stdint.h>
#include <regs.h>

typedef struct{
    uint32_t op;
    uint32_t rd;
    uint32_t rs1;
    uint32_t rs2;
    uint32_t fnc3;
    uint32_t fnc7;
} rtype;

rtype* rdecode(uint32_t, CPURegs*);
void rfnc3decode(rtype*,CPURegs*);
void rfnc7decode(rtype*,CPURegs*);
void xor(rtype*, CPURegs*);
void sub(rtype*, CPURegs*);
void add(rtype*, CPURegs*);
void sltu(rtype* ,CPURegs* );
void and(rtype*, CPURegs*);
void slt (rtype* ,CPURegs* );
void sra(rtype* , CPURegs* );
void or (rtype*, CPURegs*);
void sll(rtype* ,CPURegs* );
void srl(rtype* , CPURegs* );

#endif