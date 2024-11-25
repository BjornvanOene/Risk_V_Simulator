#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "headers/readbin.h"

/*int main(int argc, char const *argv[])
{
   printf("hello %s ", argv[1]);
    return 0;
}*/


int main(int argc, char const *argv[]) {
    readToWord( argv[1]);
    return 0;
}
