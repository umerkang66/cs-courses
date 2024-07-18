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
  int gap = n / 2;

  while (gap > 0)
  {
    int i = 0, j = gap;

    while (j < n)
    {
      if (nums[j] < nums[i])
      {
        swap(nums, i, j);
        int temp_i = i;
        while (temp_i - gap >= 0 && nums[temp_i] < nums[temp_i - gap])
        {
          swap(nums, temp_i, temp_i - gap);
          temp_i -= gap;
        }
      }

      i++;
      j++;
    }

    gap /= 2;
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
  int nums[] = {9, 5, 16, 8, 13, 6, 12, 10, 4, 2, 3};
  display(nums, 11);
  sort(nums, 11);
  display(nums, 11);

  return 0;
}
