#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *strcopy(char *s, char *malloc);

int main(void)
{
    char *s = get_string("s: ");
    if (s == NULL)
    {
        return 1;
    }

    // this copies the address, of first byte, but not copies the string
    char *t = s;

    if(strlen(t) > 0)
    {
        t[0] = toupper(t[0]);
    }

    printf("s: %s, t: %s\n", s, t);

    char *u = get_string("u: ");
    // malloc: will get the chunk of memory from computer
    // here we need (string length + 1) bytes
    char *mallocated = malloc(strlen(s) + 1);

    // malloc will return NULL, if memory is not available, NULL is a pointer (address) that points to the start of empty memory that is allocated by malloc
    if (mallocated == NULL)
    {
        return 1;
    }

    char *v = strcopy(u, mallocated);

    if(strlen(v) > 0)
    {
        v[0] = toupper(v[0]);
    }

    printf("s: %s, t: %s\n", u, v);
    free(mallocated);
    return 0;
}

char *strcopy(char *s, char *malloc)
{
    // also add the null character
    for (int i = 0, n = strlen(s); i < n+1; i++)
    {
        malloc[i] = s[i];
    }

    return malloc;
}
