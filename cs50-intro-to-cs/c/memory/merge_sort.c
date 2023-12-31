#include <cs50.h>
#include <stdio.h>

void merge(int nums[], int start, int mid, int end);
void sort(int nums[], int start, int end);

int main(void)
{
    int nums[] = {8, 9, 4, 1, 0, 3, 7, 5, 2, 6};
    int length = sizeof(nums) / sizeof(nums[0]);
    sort(nums, 0, length - 1);

    for (int i = 0; i < length; i++) {
        printf("%i", nums[i]);
    }
    printf("\n");
}

void sort(int nums[], int start, int end)
{
    // if both start and end are same element
    // only one element remains
    // return the recursive function
    if (end - start == 0)
    {
        return;
    }

    int mid = start + (end - start) / 2;
    sort(nums, start, mid);
    sort(nums, mid + 1, end);

    merge(nums, start, mid, end);
}

void merge(int nums[], int start, int mid, int end)
{
    int result[end - start + 1];
    int i = start, j = mid + 1, k = 0;

    while (i <= mid && j <= end)
    {
        if (nums[i] < nums[j])
        {
            result[k] = nums[i];
            i++;
        }
        else
        {
            result[k] = nums[j];
            j++;
        }
        k++;
    }

    while (i <= mid)
    {
        result[k] = nums[i];
        i++;
        k++;
    }

    while (j <= end)
    {
        result[k] = nums[j];
        j++;
        k++;
    }

    for (int l = 0; l < (end-start+1); l++)
    {
        nums[l + start] = result[l];
    }
}
