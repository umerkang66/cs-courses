#include <iostream>
using namespace std;

void swap(int *nums, int first, int second)
{
  int temp = nums[first];
  nums[first] = nums[second];
  nums[second] = temp;
}

// returns the index of pivot after moving to the right place
void merge(int *nums, int start, int mid, int end)
{
  int merged[end - start + 1];
  int i = start;
  int j = mid + 1;
  int k = 0;

  while (i <= mid && j <= end)
  {
    if (nums[i] <= nums[j])
      merged[k++] = nums[i++];
    else
      merged[k++] = nums[j++];
  }

  while (i <= mid)
    merged[k++] = nums[i++];

  while (j <= end)
    merged[k++] = nums[j++];

  for (int l = 0; l < end - start + 1; l++)
    nums[l + start] = merged[l];
}

void sort(int *nums, int start, int end)
{
  if (start >= end)
    return;

  int mid = (start + end) / 2;

  sort(nums, start, mid);
  sort(nums, mid + 1, end);

  merge(nums, start, mid, end);
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
  int n = sizeof(nums) / sizeof(nums[0]);
  display(nums, n);
  sort(nums, 0, n - 1);
  display(nums, n);

  return 0;
}
