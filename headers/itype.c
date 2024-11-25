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
    iinstr -> rd = (instr >> 7) & 0x1F;
    iinstr -> fnc3 = (instr >> 12) & 0x7;
    iinstr -> rs1 = (instr >> 15) & 0x1F;

    if (iinstr -> fnc3 == 5 || iinstr -> fnc3 == 1) {
        iinstr -> shamt = (instr >> 20) & 0x1F;
        iinstr -> shtyp = (instr >> 25) & 0x3F;
        iinstr -> imm = 0;
    } else {
        iinstr -> shamt = 0;
        iinstr -> shtyp = 0;
        iinstr -> imm = signextend12((instr >> 20) & 0xFFF);
    }
    return iinstr;
}

void ifnc3decode(itype* iinstr, CPURegs* reg){
    switch(iinstr -> fnc3) {
        case
    }
}