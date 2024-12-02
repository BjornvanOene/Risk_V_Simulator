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
    int ecallDecode = reg->x[17];
    switch(ecallDecode) {
        case 10:
            return 1;
            break;
        default:
            break;
    }
    return 0;
}


int compCode(uint32_t *instr, CPURegs *regs, uint32_t *pc, uint8_t* sp) {
    uint32_t op = (instr[*pc/4] & 0b00000000000000000000000001111111);
    
    switch(op) {
        case 19: {// send to itype
            itype* iinstr = decodei(instr[*pc/4], regs);
            ifnc3decode(iinstr,regs);
            break;
        }
        case 99: { // Send to btype
            btype* binstr = decodeb(instr[*pc/4],regs);
            fnc3bDecode(binstr,regs,pc);
            break;
        }
        case 103:
        case 111:{// send to jtype
            jtype* jinstr = decodej(instr[*pc/4],regs);
            jfnc3decode(jinstr,regs,pc);
            break;
        }
        case 51:{// Send to rtype
            rtype* rinstr = rdecode(instr[*pc/4],regs);
            rfnc3decode(rinstr, regs);
            break;
        }
        case 35:
        case 3:{// Send to stype
            stype* sinstr = sdecode(instr[*pc/4],regs);
            sfnc3decode(sinstr,regs,sp);
            break;
        }
        case 55:{// Send to utype
            utype* uinstr = udecode(instr[*pc/4],regs);
            lui(uinstr,regs);
            break;
        }
        case 115:{// Detect ecall
            if(ecall(instr[*pc/4],regs)){
                return 1;
            }
        }
        default:
            break;
    }
    return 0;

}