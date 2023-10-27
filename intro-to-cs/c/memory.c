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

    x[0] = 70;
    x[1] = 71;
    x[2] = 73;
    
    // we should free the memory
    free(x);
    return 0;
}
