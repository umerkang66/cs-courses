#include <stdio.h>
#include <cs50.h> 
#include <string.h>

int main(void)
{
    char *s = get_string("s: ");
    char *t = get_string("t: ");

    if (strcmp(s, t) == 0)
    {
        printf("Same\n");
    }
    else 
    {
        printf("Different\n");
    }

    // compare the characters at the first memory address of both strings
    // becuase char is a primitive, that's why
    if (*s == *t)
    {
        printf("Same\n");
    }
    else 
    {
        printf("Different\n");
    }

    printf("%p, %p\n", &s, &t);
}
