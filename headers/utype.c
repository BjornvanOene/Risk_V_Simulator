#include "utype.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "regs.h"

utype* udecode(unsigned int instr, CPURegs* reg) {
    utype* uinstr = malloc(sizeof(utype));
    if (uinstr == NULL) {
        return NULL;
    }
    uinstr -> op = (instr & 0x3F);
    uinstr -> rd = (instr >> 7) & 0x1F;
    uinstr -> imm = (instr >> 12);
    return uinstr;
}
void lui(utype* uinstr, CPURegs* reg) {
    int val = (uinstr -> imm) << 12;
    reg -> x[(uinstr->rd)] = val;

    free(uinstr);
    return;
}
