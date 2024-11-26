#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "headers/readbin.h"
#include "headers/regs.h"
#include "headers/decoder.h"

/*int main(int argc, char const *argv[])
{
   printf("hello %s ", argv[1]);
    return 0;
}*/

uint8_t* initsp(){
    uint8_t* sp = (uint8_t*) malloc(sizeof(uint8_t)*0x00100000);
    if(sp=NULL) {
        printf("Failure: Stack pointer");
    }
    return sp;
}

void printStacktoTerm(uint8_t* sp, int32_t val){
    for (int8_t i = 100; i < 136; i += 4) {
        printf("%0x: %u, %u, %u, %u\n", i, sp[i], sp[i+1], sp[i+2], sp[i+3]);
    }
    printf("\n");
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

int main(int argc, char const *argv[]) {
    readToWord( argv[1]);
    return 0;
}
