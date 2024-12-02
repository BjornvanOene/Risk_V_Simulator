#include <stdlib.h>
#include "regs.h"

CPURegs* init_regs() {
    CPURegs* reg = (CPURegs*)malloc(sizeof(CPURegs)); 
    if (reg == NULL) {
        return NULL;
    }

    for (int i = 0; i < 32; i++) {
        reg->x[i] = 0;
    }

    return reg; 
}
