#include "stype.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "regs.h"
#include "jtype.h"

int32_t stack(int32_t addr, int32_t offset, uint8_t* sp){
    int32_t stackpointer = (addr + offset);
    return stackpointer;
}

stype* sdecode(unsigned int instr, CPURegs* reg) {
    stype* sinstr = malloc(sizeof(stype));
    if (sinstr == NULL) {
        return NULL;
    }
    sinstr->op = instr & 0x7F;
    sinstr->fnc3 = (instr >> 12) & 0x7;

    if (sinstr->op == 3){
        sinstr->rd = (instr >> 7) & 0x1F;
        sinstr->rs1 = (instr >> 15) & 0x1F;
        sinstr->imm = signextend12((instr >> 20) & 0xFFF);
    } else {
        sinstr -> rs1 = (instr & 0x01F00000) >> 20;
        sinstr -> rs2 = (instr & 0x000F8000) >> 15;

        int fivefirst = (instr >> 7) & 0x1F;
        int lastseven = (instr & 0xFE000000);

        int both = (fivefirst | (lastseven << 5));

        if (both & (1<<11)) {
            both |= 0xFFFFF000;
        }
        sinstr -> imm = both;
    }
    return sinstr;
}
void sfnc3decode(stype* sinstr, CPURegs* reg, uint8_t* sp) {
    switch(sinstr -> op){
        case 35:
            storefncs(sinstr,reg,sp);
            break;
        case 3:
            loadfncs(sinstr,reg,sp);
            break;
        default:
            break;
    }
    free(sinstr);
    return;
}
void storefncs(stype* sinstr, CPURegs* reg, uint8_t* sp){
    switch(sinstr->fnc3){
        case 0:
            sb(sinstr,reg,sp);
            break;
        case 1:
            sh(sinstr,reg,sp);
            break;
        case 2:
            sw(sinstr,reg,sp);
            break;
        default:
            break;
    }
    return;
}
void sw(stype* sinstr, CPURegs* reg, uint8_t* sp) {
    uint8_t firstbytes = (reg->x[sinstr->rs1] & 0x000000FF);
    uint8_t uppermidbytes = (reg->x[sinstr->rs1] & 0x0000FF00) >> 8;
    uint8_t lowermidbytes = (reg->x[sinstr->rs1] & 0x00FF0000) >> 16;
    uint8_t finalbytes = (reg->x[sinstr->rs1] & 0xFF000000) >> 24;

    int addr = reg->x[sinstr->rs2];
    int offset = sinstr->imm;

    sp[stack(addr,offset,sp)+3] = finalbytes;
    sp[stack(addr,offset,sp)+2] = lowermidbytes;
    sp[stack(addr,offset,sp)+1] = uppermidbytes;
    sp[stack(addr,offset,sp)] = firstbytes;
    return;
}

void sh(stype* sinstr, CPURegs* reg, uint8_t* sp) {
    uint8_t firstbytes = (reg->x[sinstr->rs1] & 0x000000FF);
    uint8_t uppermidbytes = (reg->x[sinstr->rs1] & 0x0000FF00) >> 8;

    int addr = reg->x[sinstr->rs2];
    int offset = sinstr->imm;

    sp[stack(addr,offset,sp)+1] = uppermidbytes;
    sp[stack(addr,offset,sp)] = firstbytes;
    return;
}

void sb(stype* sinstr, CPURegs* reg, uint8_t* sp){
    uint8_t firstbytes = (reg->x[sinstr->rs1] & 0x000000FF);
    int addr = reg->x[sinstr->rs2];
    int offset = sinstr->imm;
    sp[stack(addr,offset,sp)] = firstbytes;
    return;
}

void loadfncs(stype* sinstr, CPURegs* reg, uint8_t* sp){
        switch(sinstr->fnc3){
        case 0:
            lb(sinstr,reg,sp);
            break;
        case 1:
            lh(sinstr,reg,sp);
            break;
        case 2:
            lw(sinstr,reg,sp);
            break;
        default:
            break;
        }
        return;

    }

void lw(stype* sinstr, CPURegs* reg, uint8_t* sp) {
    int addr = reg->x[sinstr->rs2];
    int offset = sinstr->imm;

    int firstbytes = sp[stack(addr,offset,sp)];
    int uppermidbytes = sp[stack(addr,offset,sp)+1];
    int lowermidbytes = sp[stack(addr,offset,sp)+2];
    int finalbytes = sp[stack(addr,offset,sp)+3];

    reg -> x[sinstr->rd] = (int32_t) (firstbytes << 24 | uppermidbytes << 16 | lowermidbytes << 8 | finalbytes <<0);
    
    return;
}

void lh(stype* sinstr, CPURegs* reg, uint8_t* sp) {
    int addr = reg->x[sinstr->rs2];
    int offset = sinstr->imm;

    int firstbytes = sp[stack(addr,offset,sp)];
    int uppermidbytes = sp[stack(addr,offset,sp)+1];

    reg -> x[sinstr->rd] = (int16_t) (firstbytes << 0 | uppermidbytes << 8);
    
    return;
}

void lhu(stype* sinstr, CPURegs* reg, uint8_t* sp) {
    int addr = reg->x[sinstr->rs2];
    int offset = sinstr->imm;

    int firstbytes = sp[stack(addr,offset,sp)];
    int uppermidbytes = sp[stack(addr,offset,sp)+1];

    reg -> x[sinstr->rd] = firstbytes << 0 | uppermidbytes << 8;
    
    return;
}


void lb(stype* sinstr, CPURegs* reg, uint8_t* sp) {
    int addr = reg->x[sinstr->rs2];
    int offset = sinstr->imm;

    int firstbytes = sp[stack(addr,offset,sp)];

    reg -> x[sinstr->rd] = (int8_t) firstbytes;
    
    return;
}
void lbu(stype* sinstr, CPURegs* reg, uint8_t* sp) {
    int addr = reg->x[sinstr->rs2];
    int offset = sinstr->imm;

    int firstbytes = sp[stack(addr,offset,sp)];

    reg -> x[sinstr->rd] = firstbytes;
    
    return;
}