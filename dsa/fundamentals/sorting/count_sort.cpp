#include <iostream>
using namespace std;

int find_max(int *nums, int n)
{
  int largest = nums[0];
  for (int i = 0; i < n; i++)
    largest = max(largest, nums[i]);
  return largest;
}

void sort(int *nums, int n)
{
  int max = find_max(nums, n);

  int arr[max + 1];
  for (int i = 0; i < max + 1; i++)
    arr[i] = 0;

  for (int i = 0; i < n; i++)
    arr[nums[i]] += 1;

  int k = 0;
  for (int i = 0; i < max + 1; i++)
  {
    for (int j = 0; j < arr[i]; j++)
      nums[k++] = i;
  }
}

void display(int *nums, int n)
{
  for (int i = 0; i < n; i++)
    cout << nums[i] << ' ';
  cout << endl;
}

int main()
{
  int nums[] = {5, 8, 3, 4, 3, 9, 1, 9};
  display(nums, 8);
  sort(nums, 8);
  display(nums, 8);

  return 0;
}
