#include <btype.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <regs.h>

int32_t decodeOffset(uint32_t instr) {
    int first4 = (instr >> 8) & 0xF;
    int follow6 = (instr >> 25) & 0b1111111;
    int next1 = (instr >> 7) & 0x1;
    int last = (instr >> 31) & 0x1;

    int32_t offset = (last << 11) |
                     (next1 << 10)|
                     (follow6 << 4) |
                     (first4 );
    
    if(last){
        offset = offset | 0xFFFFF000;
    }
    offset = offset << 1;

    return offset;
}

btype* decodeb(uint32_t instr, CPURegs* reg){
    btype* binstr = malloc(sizeof(btype));
    if(binstr == NULL) {
        return NULL;
    }

    binstr -> op = instr & 0x7F;
    binstr -> fnc3 = (instr >> 12) & 0x7;
    binstr -> rs1 = (instr >> 15) & 0x1F;
    binstr -> rs2 = (instr >> 20) & 0x1F;

    binstr -> offset = decodeOffset(instr) - 4;

    return binstr;
}

void fnc3bDecode(btype* binstr, CPURegs* reg, uint32_t *pc) {
    switch(binstr -> fnc3)
    {
    case 0:
        beq(binstr, reg, pc);
        break;
    case 1:
        bne(binstr, reg, pc);
        break;
    case 4:
        blt(binstr, reg, pc);
        break;
    case 5:
        bge(binstr, reg, pc);
        break;
    case 6:
        bltu(binstr, reg, pc);
        break;
    case 7:
        bgeu(binstr, reg, pc);
        break;
    }
}

void bge(btype* binstr, CPURegs* reg, uint32_t *pc) {
    if (reg -> x[binstr -> rs1] >= reg -> x[binstr -> rs2]) {
        *pc = *pc + binstr->offset;
    }
    return;
}

void bltu(btype* binstr, CPURegs* reg, uint32_t *pc) {
    if (((uint32_t)reg -> x[binstr -> rs1]) < ((uint32_t)reg -> x[binstr -> rs2])){
        *pc = *pc + binstr->offset;
    }
    return; 
}

void bgeu(btype* binstr, CPURegs* reg, uint32_t *pc) {
    if (((uint32_t)reg -> x[binstr -> rs1]) >= ((uint32_t)reg -> x[binstr -> rs2])){
        *pc = *pc + binstr->offset;
    }
    return; 
}

void blt(btype* binstr, CPURegs* reg, uint32_t *pc) {
    if (reg -> x[binstr -> rs1] < reg -> x[binstr -> rs2]) {
        *pc = *pc + binstr->offset;
    }
    return;
}

void bne(btype* binstr, CPURegs* reg, uint32_t *pc) {
    if (reg -> x[binstr -> rs1] != reg -> x[binstr -> rs2]) {
        *pc = *pc + binstr->offset;
    }
    return;
}

void beq(btype* binstr, CPURegs* reg, uint32_t *pc) {
    if (reg -> x[binstr -> rs1] == reg -> x[binstr -> rs2]) {
        *pc = *pc + binstr->offset;
    }
    return;
}