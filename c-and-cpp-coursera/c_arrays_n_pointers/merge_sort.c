#include <stdio.h>

void print_array(int array[], int SIZE);
void merge_sort(int array[], int start, int end);
void merge(int array[], int start, int mid, int end);

int main(void)
{
    int nums[5] = {5, 2, 3, 4, 1};
    print_array(nums, 5);
    merge_sort(nums, 0, 5 - 1);
    print_array(nums, 5);
}

void merge_sort(int array[], int start, int end)
{
    if (start >= end)
    {
        return;
    }
    int mid = start + (end - start) / 2;
    merge_sort(array, start, mid);
    merge_sort(array, mid + 1, end);
    merge(array, start, mid, end);
}

void merge(int array[], int start, int mid, int end)
{
    int i = start, j = mid + 1, k = 0;
    int result_length = end - start + 1;
    int result[result_length];
    while (i <= mid && j <= end)
    {
        if (array[i] < array[j])
        {
            result[k] = array[i];
            i++;
        }
        else
        {
            result[k] = array[j];
            j++;
        }
        k++;
    }
    while (i <= mid)
    {
        result[k] = array[i];
        i++;
        k++;
    }
    while (j <= end)
    {
        result[k] = array[j];
        j++;
        k++;
    }
    for (int l = 0; l < result_length; l++)
    {
        array[l + start] = result[l];
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
