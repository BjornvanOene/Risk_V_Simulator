#include <stdio.h>
#include <stdint.h>
#include "decoder.h"
#include "btype.h"
#include "itype.h"
#include "jtype.h"
#include "stype.h"
#include "rtype.h"
#include "utype.h"

int ecall(uint32_t instr, CPURegs* reg){
    
    switch(ecallDecode) {
        case 10:
            return 1;
            break;
        default:
            break;
    }
}

int  