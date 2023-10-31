#include <stdio.h>

int main(void)
{
    int x;
    printf("x: ");
    scanf("%i", &x);
    printf("x: %i\n", x);

    char *s;
    printf("s: ");
    // we don't need the '&', because char * already points to the first char of string
    scanf("%s", s);
    printf("s: %s\n", s);
}
