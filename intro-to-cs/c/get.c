#include <stdio.h>

int main(void)
{
    int x;
    printf("x: ");
    scanf("%i", &x);
    printf("x: %i\n", x);

    // if the size is 4, we can store 3 characters plus \0 character
    // if we store more than 4 characters(null including), we will be touching the memory that we shouldn't have
    // so checkout the phonebook.c
    char s[4];
    printf("s: ");
    // we don't need the '&', because char * already points to the first char of string
    scanf("%s", s);
    printf("s: %s\n", s);
}
