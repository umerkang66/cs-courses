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
}
