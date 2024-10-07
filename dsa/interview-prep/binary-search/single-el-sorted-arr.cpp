// https://leetcode.com/problems/single-element-in-a-sorted-array/

#include <iostream>
using namespace std;

int single_element(int *nums, int length)
{
  if (length == 0)
    return -1;
  if (length == 1)
    return nums[0];

  int start = 0;
  int end = length - 1;

  while (start <= end)
  {
    int mid = start + (end - start) / 2;

    // check for if mid is first and last element corner cases
    if (mid == 0 && nums[mid] != nums[mid + 1])
      return nums[mid];
    if (mid == length - 1 && nums[mid] != nums[mid - 1])
      return nums[mid];

    if (nums[mid] != nums[mid + 1] && nums[mid] != nums[mid - 1])
      return nums[mid];

    if (mid % 2 == 0)
    {
      if (nums[mid] == nums[mid - 1])
        end = mid - 1;
      else
        start = mid + 1;
    }
    else
    {
      if (nums[mid] == nums[mid - 1])
        start = mid + 1;
      else
        end = mid - 1;
    }
  }

  return -1;
}

int main()
{
  int nums[] = {1, 1, 2, 3, 3, 4, 4, 8, 8};
  int length = sizeof(nums) / sizeof(nums[0]);
  cout << single_element(nums, length) << endl;

  int nums2[] = {3, 3, 7, 7, 10, 11, 11};
  int length2 = sizeof(nums2) / sizeof(nums2[0]);
  cout << single_element(nums2, length2) << endl;

  int nums3[] = {1, 2, 2, 3, 3};
  int length3 = sizeof(nums3) / sizeof(nums3[0]);
  cout << single_element(nums3, length3) << endl;

  int nums4[] = {1, 1, 2, 2, 3};
  int length4 = sizeof(nums4) / sizeof(nums4[0]);
  cout << single_element(nums4, length4) << endl;

  return 0;
}
