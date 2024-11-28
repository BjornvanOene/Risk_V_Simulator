#include "jtype.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "regs.h"

int32_t signextend(int32_t val) {
    if (val & 0x800) { // Evaluate 12th bit
        val |= ~0xFFF; // Maintain sign by setting upper bits to 1
    }
    return val;
}

jtype* decodej(uint32_t instr, CPURegs* reg){
    jtype* jinstr = malloc(sizeof(jtype));
    if(jinstr == NULL) {
        return NULL;
    }


    jinstr -> op = instr & 0x7F;

    if(jinstr -> op == 103){
    jinstr -> op = instr & 0x7F;
    jinstr -> rd = (instr >> 7) & 0x1F;
    jinstr -> rs1 = (instr >> 15) & 0x1F;
    jinstr -> imm = signextend((instr >> 20) & 0xFFF);
    jinstr -> fnc3 = (instr >> 12) & 0x7;
    
    } else {
    jinstr -> rd = (instr >> 7) & 0x1F;

    int fir10bits = instr & 0x7FE0000;
    int bit11 = instr & 0x00100000;
    int finbit = instr & 0x80000000;
    int rembits = instr & 0x000FF000;

    int32_t offset = (fir10bits >> 20 ) |
                      (bit11 >> 9) |
                      (rembits >> 1) |
                      (finbit >> 11);
    offset = (offset << 20) >> 20;

    jinstr -> imm = offset;
    }

    return jinstr;
}

void jfnc3decode(jtype* jinstr, CPURegs* reg, uint32_t* pc) {
    switch (jinstr -> op) {
        case 111:
            jal(jinstr, reg, pc);
            break;
        case 103:
            jalr(jinstr, reg, pc);
            break;
        default:
            break;
    }

    free(jinstr);
    return;
}

void jalr(jtype* jinstr, CPURegs* reg, uint32_t* pc) {
    reg -> x[jinstr->rd] = *pc + 4;
    int32_t newadd = jinstr -> imm + reg -> x[jinstr->rs1];
    newadd = newadd & 0xFFFFFFFE;
    *pc = newadd;
    return;
}

void jal(jtype* jinstr, CPURegs* reg, uint32_t* pc) {
    reg -> x[jinstr->rd] = *pc;
    *pc = *pc + jinstr -> imm -4;
    return;

}