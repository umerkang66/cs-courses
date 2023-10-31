#include <stdio.h>

void swap(int *a, int *b);

int main(void)
{
    int x = 1;
    int y = 2;

    printf("x is %i, y is %i\n", x, y);
    swap(&x, &y);
    printf("x is %i, y is %i\n", x, y);
}

// when we are passing the functions, we are passing the arguments as 'values', not as 'pointers'
void swap(int *a, int *b)
{
    // the value of 'a pointer' to temp variable
    int temp = *a;
    // add the value of 'b pointer' to 'a', go to address where 'a points', then add the value of 'a pointer' there
    *a = *b;
    // add the value of 'temp' to 'b', go to address where 'b points', then add the value of temp there
    *b = temp;
}
