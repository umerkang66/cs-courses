#include <iostream>
using namespace std;

int container_with_most_water_BF(int *nums, int length)
{
  int max_area = -1;

  for (int i = 0; i < length; i++)
  {
    for (int j = i + 1; j < length; j++)
    {
      int smaller = min(nums[i], nums[j]);
      int area = smaller * (j - i);
      max_area = max(area, max_area);
    }
  }

  return max_area;
}

int container_with_most_water_optimized(int *nums, int length)
{
  // TWO POINTERS
  int i = 0, j = length - 1;
  int max_area = -1;

  while (i < j)
  {
    int height = min(nums[i], nums[j]);
    int width = j - i;
    int area = height * width;
    max_area = max(max_area, area);

    if (nums[i] < nums[j])
    {
      i++;
    }
    else
    {
      j++;
    }
  }

  return max_area;
}

int main()
{
  int nums[] = {1, 8, 6, 2, 5, 4, 8, 3, 7};
  int length = sizeof(nums) / sizeof(nums[0]);

  cout << container_with_most_water_BF(nums, length) << endl;
  cout << container_with_most_water_optimized(nums, length) << endl;

  return 0;
}
