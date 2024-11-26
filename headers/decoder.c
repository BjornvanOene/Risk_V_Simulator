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


int compCode(uint32_t* instr, CPURegs* reg, int* pc, uint8_t* sp) {
    uint32_t* op = (instr[*pc/4] & 0b00000000000000000000000001111111);
    
    switch(*op) {
        case 19: // send to itype
            itype* iinstr = decodei(instr[*pc/4], reg);
            ifnc3decode(iinstr,reg);
            break;
        case 99: // Send to btype
            btype* binstr = bdecode(instr[*pc/4],reg);
            fnc3bDecode(binstr,reg,pc);
            break;
        case 111 | 103:
            jtype* jinstr = decodej(instr[*pc/4],reg);
            jfnc3decode(jinstr,reg,pc);
            break;
        case 51:
            rtype* rinstr = rdecode(instr[*pc/4],reg);
            rfnc3decode(rinstr, reg);
            break;
        case 35 | 3:
            stype* sinstr = sdecode(instr[*pc/4],reg);
            sfnc3decode(sinstr,reg,pc);
            break;
        case 55:
            utype* uinstr = udecode(instr[*pc/4],reg);
            lui(uinstr,reg);
            break;
        case 115:
            if(ecall(instr[*pc/4],reg)){
                return 1;
            }
        default:
            break;
    }
    return 0;

}