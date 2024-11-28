#include "itype.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "regs.h"
#include "jtype.h"

itype* decodei(uint32_t instr, CPURegs* reg){
    itype* iinstr = malloc(sizeof(itype));
    if(iinstr == NULL) {
        return NULL;
    }
    iinstr -> op = instr & 0x7F;
    iinstr -> rs1 = (instr >> 15) & 0x1F;
    iinstr -> rd = (instr >> 7) & 0x1F;
    iinstr -> fnc3 = (instr >> 12) & 0x7;
    
    if (iinstr -> fnc3 == 5 || iinstr -> fnc3 == 1) {
        iinstr -> shamt = (instr >> 20) & 0x1F;
        iinstr -> shtyp = (instr >> 25) & 0x3F;
        iinstr -> imm = 0;
    } else {
        iinstr -> shamt = 0;
        iinstr -> shtyp = 0;
        iinstr -> imm = signextend((instr >> 20) & 0xFFF);
    }
    return iinstr;
}

void ifnc3decode(itype* iinstr, CPURegs* reg){
    switch(iinstr -> fnc3) {
        case 0:
            addi(iinstr,reg);
            break;
        case 1: 
            slli(iinstr,reg);
            break;
        case 2:
            slti(iinstr,reg);
            break;
        case 3:
            sltiu(iinstr,reg);
            break;
        case 4:
            xori(iinstr,reg);
            break;
        case 5:
            if(iinstr->shtyp == 0) {
                srli(iinstr,reg);
            } else {
                srai(iinstr,reg);
            }
            break;
        case 6: 
            ori(iinstr,reg);
            break;
        case 7:
            andi(iinstr,reg);
            break;
    }
    free(iinstr);
}

void addi(itype* iinstr, CPURegs* reg) {
    reg -> x[(iinstr->rd)] = reg -> x[(iinstr->rs1)] + iinstr -> imm;
    return;
}
void andi(itype* iinstr, CPURegs* reg) {
    reg -> x[(iinstr->rd)] = reg -> x[(iinstr->rs1)] & iinstr -> imm;
    return;
}
void ori(itype* iinstr, CPURegs* reg) {
    reg -> x[(iinstr->rd)] = reg -> x[(iinstr->rs1)] | iinstr -> imm;
    return;
}
void xori(itype* iinstr, CPURegs* reg) {
    reg -> x[(iinstr->rd)] = reg -> x[(iinstr->rs1)] ^ iinstr -> imm;
    return;
}
void sltiu(itype* iinstr, CPURegs* reg) {
    if ((uint32_t)(reg->x[(iinstr->rs1)]) < (uint32_t)(iinstr->imm)){
        reg -> x[iinstr->rd] = 1;
    } else{
         reg -> x[iinstr->rd] = 0;
    }
    return;
}
void slti(itype* iinstr, CPURegs* reg) {
    if ((reg->x[(iinstr->rs1)]) < (iinstr->imm)){
        reg->x[(iinstr->rd)] = 1;
    } else{
        reg->x[(iinstr->rd)] = 0;
    }
    return;
}
void srli(itype* iinstr, CPURegs* reg) {
    reg -> x[(iinstr->rd)] = (((uint32_t)reg -> x[(iinstr->rs1)]) >> (iinstr->shamt));
    return;
}
void srai(itype* iinstr, CPURegs* reg) {
    reg -> x[(iinstr->rd)] = ((reg->x[(iinstr->rs1)]) >> (iinstr->shamt));
    return;
}
void slli(itype* iinstr, CPURegs* reg) {
    reg -> x[(iinstr->rd)] = (((uint32_t)reg->x[(iinstr->rs1)] << (iinstr->shamt)));
    return;
}
