#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "readbin.h"

int readToWord( char a[]) {
    //const char *filename = "example.bin";
    FILE *file = fopen(a, "rb");  // Open file in binary mode

    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Determine file size
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);

    // Check if the file size is a multiple of 4 (32 bits)
    if (fileSize % 4 != 0) {
        fprintf(stderr, "Error: File size is not a multiple of 4 bytes (32 bits)\n");
        fclose(file);
        return 1;
    }

    // Calculate number of 32-bit words
    size_t numWords = fileSize / 4;

    // Allocate memory for the array of 32-bit words
    uint32_t *wordArray = (uint32_t *)malloc(numWords * sizeof(uint32_t));
    if (wordArray == NULL) {
        perror("Memory allocation failed");
        fclose(file);
        return 1;
    }

    // Read 32-bit words into the array
    size_t wordsRead = fread(wordArray, sizeof(uint32_t), numWords, file);
    if (wordsRead != numWords) {
        perror("Error reading file");
        free(wordArray);
        fclose(file);
        return 1;
    }
    
    // Print the 32-bit words
    printf("File read successfully. Total words: %zu\n", numWords);
    for (size_t i = 0; i < numWords; i++) {
        printf("Word %zu: 0x%08X\n", i, wordArray[i]);
    }

    // Clean up
    free(wordArray);
    fclose(file);

    return 0;
}