#ifndef READBINH
#define READBINH

#include <stdint.h>

uint32_t* readToWord( char a[]);
void write_res_file(const char *filename, int32_t registers[32]);

#endif