#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "regs.h"
#include "decoder.h"
#include "readbin.h"
#include "btype.h"
#include "itype.h"
#include "jtype.h"
#include "rtype.h"
#include "stype.h"
#include "utype.h"

/*int main(int argc, char const *argv[])
{
   printf("hello %s ", argv[1]);
    return 0;
}*/

uint8_t* initsp(){
    uint8_t* sp = (uint8_t*) malloc(sizeof(uint8_t)*0x00100000);
    if(sp==NULL) {
        printf("Failure: Stack pointer");
    }
    return sp;
}

void printStacktoTerm(uint8_t* sp, int32_t val){
    val = val*4;
    for (uint8_t i = 100; i < 152; i += 4) {
        printf("%0x: %u, %u, %u, %u\n", i, sp[i], sp[i+1], sp[i+2], sp[i+3]);
    }
    printf("\n");
}
void printRegtoTerm(CPURegs* reg){
    for (uint32_t i = 0; i<32; i+=1){
        printf("x%D:%0x\n", i, reg->x[i]);
    }
}
int lengthofinstr(uint32_t* len){
    int i = 0;
    while (len[i] != 0) {
        i++;
    }
    return i;
}

void loadtomem(uint8_t* sp, uint32_t* instr) {
    uint32_t totalinstr = 128; //64 

    for (int j = 0; j < totalinstr; j++) {
        sp[j * 4] = (instr[j] & 0x000000FF);
        sp[j * 4 + 1] = (instr[j] & 0x0000FF00) >> 8;
        sp[j * 4 + 2] = (instr[j] & 0x00FF0000) >> 16;
        sp[j * 4 + 3] = (instr[j] & 0xFF000000) >> 24;
    }
    return;
}

int main(int argc, char *argv[]) {
    
    CPURegs* regs = init_regs();
    uint8_t* sp = initsp(); 
    uint32_t* IntructionArray;
    if(argv[1]){
        IntructionArray = readToWord(argv[1]);
    } else{
        IntructionArray = readToWord("tests/task3/loop.bin");

    }
    //uint32_t* IntructionArray = readToWord(argv[1]);
    loadtomem(sp, IntructionArray);

    uint32_t pcval = 0;
    uint32_t *pc = &pcval;
    //uint32_t len = lengthofinstr(IntructionArray) << 2;

    while (1) {
        if (compCode(IntructionArray, regs, pc, sp)){
            break;
        }
        *pc = *pc+4;
        regs -> x[0] = 0;
    }
    printRegtoTerm(regs);
    free(sp);
    free(IntructionArray);
    return 0;
}
