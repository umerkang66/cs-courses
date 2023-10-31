#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    // sizeof(int) is 4
    // malloc will return the address of first byte
    // it means we can store 3 integers
    int *x = malloc(3 * sizeof(int));
    if (x == NULL)
    {
        return 1;
    }

    // add 4 bytes of memory 3 times, because INT takes 4 bytes
    x[0] = 70;
    x[1] = 71;
    x[2] = 73;
    // NOTE: the below line could break the program, because we only we have only 12 bytes available that can be ditected through valgrind
    // x[3] = 74;
    
    // we should free the memory
    free(x);
    return 0;
}

// to debug memory related bugs
// valgrind ./memory
