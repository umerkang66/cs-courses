#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    // if we don't initialize the array, garbage values will be added
    // some garbage values will be 0, other garbage values will be random values, becuase are poking around the random computer memory
    // DON'T DO THIS, Always initialize the values
    int scores[1024];
    for (int i = 0; i < 1024; i++)
    {
        printf("%i\n", scores[i]);
    }
}
