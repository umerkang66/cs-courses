#include <iostream>
using namespace std;

void swap(int *nums, int first, int second)
{
  int temp = nums[first];
  nums[first] = nums[second];
  nums[second] = temp;
}

void sort(int *nums, int n)
{
  for (int i = 1; i < n; i++)
  {
    for (int j = i; j > 0; j--)
    {
      if (nums[j] < nums[j - 1])
        swap(nums, j, j - 1);
      else
        break;
    }
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
  int nums[] = {5, 8, 4, 3, 9, 1};
  display(nums, 6);
  sort(nums, 6);
  display(nums, 6);

  return 0;
}
