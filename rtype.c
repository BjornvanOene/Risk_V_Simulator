#include "rtype.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "regs.h"

rtype* rdecode(uint32_t instr, CPURegs* reg) {
    rtype* rinstr = malloc(sizeof(rtype));
    if (rinstr == NULL) {
        return NULL;
    }

    rinstr->op = instr & 0x7F;
    rinstr->rd = (instr >> 7) & 0x1F;
    rinstr->fnc3 = (instr >> 12) & 0x7;
    rinstr->rs1 = (instr >>15) & 0x1F;
    rinstr->rs2 = (instr >> 20) & 0x1F;
    rinstr->fnc7 = (instr >> 25) & 0x7F;
    return rinstr;
}

void rfnc3decode(rtype* rinstr, CPURegs* reg) {
    switch(rinstr->fnc3) {
        case 0:
            rfnc7decode(rinstr,reg);
            break;
        case 1:
            sll(rinstr,reg);
            break;
        case 2:
            slt(rinstr,reg);
            break;
        case 3:
            sltu(rinstr,reg);
            break;
        case 4:
            xor(rinstr,reg);
        case 5:
            if(rinstr->fnc7 == 0){
                srl(rinstr,reg);
            } else {
                sra(rinstr,reg);
            } break;
        case 6:
            or(rinstr,reg);
            break;
        case 7:
            and(rinstr,reg);
            break;
        default:
            break;
    }
    free(rinstr);
    return;
}
void rfnc7decode(rtype* rinstr, CPURegs* reg) {
    switch(rinstr->fnc7) {
        case 32:
            sub(rinstr,reg);
            break;
        case 0:
            add(rinstr,reg);
            break;
        default:
            break;
    }
    return;
}

void or(rtype* rinstr, CPURegs* reg) {
    reg -> x[rinstr->rd] = reg -> x[rinstr->rs1] | reg -> x[rinstr->rs2];
    return;
}
void and(rtype* rinstr, CPURegs* reg) {
    reg -> x[rinstr->rd] = reg -> x[rinstr->rs1] & reg -> x[rinstr->rs2];
    return;
}
void xor(rtype* rinstr, CPURegs* reg) {
    reg -> x[rinstr->rd] = reg -> x[rinstr->rs1] ^ reg -> x[rinstr->rs2];
    return;
}
void add(rtype* rinstr, CPURegs* reg) {
    reg -> x[rinstr->rd] = reg -> x[rinstr->rs1] + reg -> x[rinstr->rs2];
    return;
}
void sub(rtype* rinstr, CPURegs* reg) {
    reg -> x[rinstr->rd] = reg -> x[rinstr->rs1] - reg -> x[rinstr->rs2];
    return;
}
void sra(rtype* rinstr, CPURegs* reg) {
    reg -> x[rinstr->rd] = (reg -> x[rinstr->rs1] >> reg -> x[rinstr->rs2] & 0x1F);
    return;
}
void srl(rtype* rinstr, CPURegs* reg) {
    reg -> x[rinstr->rd] = ((uint32_t)reg -> x[rinstr->rs1] >> reg -> x[rinstr->rs2] & 0x1F);
    return;
}
void sltu(rtype* rinstr, CPURegs* reg) {
    if((uint32_t)(reg->x[rinstr->rs1]) < (uint32_t)(reg->x[rinstr->rs2])){
        reg -> x[rinstr->rd] = 1;
    } else {
        reg -> x[rinstr->rd] = 0;
    }
    return;
}
void slt(rtype* rinstr, CPURegs* reg) {
    if((reg->x[rinstr->rs1]) < (reg->x[rinstr->rs2])){
        reg -> x[rinstr->rd] = 1;
    } else {
        reg -> x[rinstr->rd] = 0;
    }
    return;
}
void sll(rtype* rinstr, CPURegs* reg) {
    reg -> x[rinstr->rd] = ((uint32_t)(reg->x[rinstr->rs1]) << (reg->x[rinstr->rs2] & 0x1F));
    return;
}