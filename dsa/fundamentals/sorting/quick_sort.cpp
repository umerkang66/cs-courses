#include <iostream>
using namespace std;

void swap(int *nums, int first, int second)
{
  int temp = nums[first];
  nums[first] = nums[second];
  nums[second] = temp;
}

// returns the index of pivot after moving to the right place
int get_partition(int *nums, int start, int end)
{
  int i = start;
  int j = end - 1;
  int pivot = end;

  while (i <= j)
  {
    while (i <= j && nums[i] < nums[pivot])
      i++;
    while (i <= j && nums[j] > nums[pivot])
      j--;

    if (i < j)
    {
      swap(nums, i, j);
      i++;
      j--;
    }
  }

  swap(nums, i, pivot);
  return i;
}

void sort(int *nums, int start, int end)
{
  if (start >= end)
    return;

  int pivot = get_partition(nums, start, end);

  sort(nums, start, pivot - 1);
  sort(nums, pivot + 1, end);
}

void display(int *nums, int n)
{
  for (int i = 0; i < n; i++)
    cout << nums[i] << ' ';
  cout << endl;
}

int main()
{
  int nums[] = {5, 8, 4, 3, 9, 1};
  display(nums, 6);
  sort(nums, 0, (sizeof(nums) / sizeof(nums[0])) - 1);
  display(nums, 6);

  return 0;
}
