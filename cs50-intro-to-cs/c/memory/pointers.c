#include <stdio.h>

int main(void)
{
    int n = 50;
    // the pointer stores the address of n,
    // the pointers are also stored in memory, so it should also have address
    // we can also get the address of pointer 'p' by &p
    int *p = &n;

    printf("%p , %p, %i\n", p, &p, n);
    printf("%i\n", *p);

    char *s = "HI!";
    printf("%p , %s\n", s, s);
    printf("%p , %p , %p , %p\n", &s[0], &s[1], &s[2], &s[3]);

    printf("%c , %c , %c , %c\n", *s, *(s+1), *(s+2), *(s+3));

    printf("%s , %s , %s\n", s, s+1, s+2);
}

// NOTE: How pointer arithmetic works, adding will move it to the next address in memory (based on the data type), means if the next number is integer, it will move 4 bytes, because integer takes 4 bytes, we don't have to explicitely add the pointer with 4