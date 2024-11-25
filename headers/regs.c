#include <stdlib.h>
#include "regs.h"

CPURegs* init_registers() {
    //Allocate memory
    CPURegs* reg = (CPURegs*)malloc(sizeof(CPURegs));
    if (reg == NULL) {
        //Handle failure
        return NULL;
    }

    // Initialize all registers to 0
    for (int i = 0; i < 32; i++) {
        reg->x[i] = 0;
    }

    return reg; // Return the pointer to the allocated struct
}
