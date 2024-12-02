#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "readbin.h"
#include "regs.h"

uint32_t* readToWord(char a[]) {
    //const char *filename = "example.bin";
    FILE *file = fopen(a, "rb");  // Open file in binary mode

    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }

    // Determine file size
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);

    // Check if the file size is a multiple of 4 (32 bits)
    if (fileSize % 4 != 0) {
        fprintf(stderr, "Error: File size is not a multiple of 4 bytes (32 bits)\n");
        fclose(file);
        return NULL;
    }

    // Calculate number of 32-bit words
    size_t numWords = fileSize / 4;

    // Allocate memory for the array of 32-bit words
    uint32_t *wordArray = (uint32_t *)malloc(numWords * sizeof(uint32_t));
    if (wordArray == NULL) {
        perror("Memory allocation failed");
        fclose(file);
        return NULL;
    }

    // Read 32-bit words into the array
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
        // Write the 32-bit register value in little-endian order
        fputc(value & 0xFF, file);          // Least significant byte
        fputc((value >> 8) & 0xFF, file);  // Next byte
        fputc((value >> 16) & 0xFF, file); // Next byte
        fputc((value >> 24) & 0xFF, file); // Most significant byte
    }

    fclose(file);
    printf(".res file successfully created: %s\n", filename);
}