#include <stdio.h>

void print_array(int array[], int SIZE);
void bubble_sort(int array[], int SIZE);

int main(void)
{
    int nums[5] = {5, 2, 3, 4, 1};
    print_array(nums, 5);
    bubble_sort(nums, 5);
    print_array(nums, 5);
}

void bubble_sort(int array[], int SIZE)
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE - i - 1; j++)
        {
            if (array[j] > array[j + 1])
            {
                // swap
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

void print_array(int array[], int SIZE)
{
    printf("[");
    for (int i = 0; i < SIZE; i++)
    {
        printf("%i", array[i]);
        if (i != SIZE - 1)
        {
            printf(", ");
        }
    }
    printf("]\n");
}
