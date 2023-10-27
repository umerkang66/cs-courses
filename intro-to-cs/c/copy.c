#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
    char *s = get_string("s: ");
    // this copies the address, of first byte, but not copies the string
    char *t = s;

    if(strlen(t) > 0)
    {
        t[0] = toupper(t[0]);
    }

    printf("s: %s, t: %s\n", s, t);

    char *u = get_string("u: ");
    // this copies the string
    // malloc: will get the chunk of memory from computer
    // here we need (string length + 1) bytes
    char *v = malloc(strlen(u)+1);

    // also add the null character
    for (int i = 0; i < strlen(u) + 1; i++)
    {
        v[i] = u[i];
    }

    if(strlen(v) > 0)
    {
        v[0] = toupper(v[0]);
    }

    printf("s: %s, t: %s\n", u, v);
}
