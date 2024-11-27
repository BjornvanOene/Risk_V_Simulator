#include <stdlib.h>
#include "regs.h"

CPURegs* init_regs() {
    CPURegs* reg = (CPURegs*)malloc(sizeof(CPURegs)); //Memory allocation
    if (reg == NULL) {
        //Handle failure
        return NULL;
    }

    // Initialize all regs to 0
    for (int i = 0; i < 32; i++) {
        reg->x[i] = 0;
    }

    return reg; // Return pointer to struct
}
