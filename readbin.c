#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "readbin.h"
#include "regs.h"

uint32_t* readToWord(char a[]) {
    FILE *file = fopen(a, "rb");  

    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);

    if (fileSize % 4 != 0) {
        fprintf(stderr, "Error: File size is not a multiple of 4 bytes (32 bits)\n");
        fclose(file);
        return NULL;
    }

    size_t numWords = fileSize / 4;

    uint32_t *wordArray = (uint32_t *)malloc(numWords * sizeof(uint32_t));
    if (wordArray == NULL) {
        perror("Memory allocation failed");
        fclose(file);
        return NULL;
    }

    size_t wordsRead = fread(wordArray, sizeof(uint32_t), numWords, file);
    if (wordsRead != numWords) {
        perror("Error reading file");
        free(wordArray);
        fclose(file);
        return NULL;
    }
    
    
    fclose(file);

    return wordArray;
}

void write_res_file(const char *filename, int32_t registers[32]) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        perror("Error opening file for writing");
        return;
    }

    for (int i = 0; i < 32; i++) {
        uint32_t value = registers[i];
        fputc(value & 0xFF, file);          
        fputc((value >> 8) & 0xFF, file); 
        fputc((value >> 16) & 0xFF, file); 
        fputc((value >> 24) & 0xFF, file); 
    }

    fclose(file);
    printf(".res file successfully created: %s\n", filename);
}