// https://leetcode.com/problems/search-in-rotated-sorted-array/

#include <iostream>
using namespace std;

int binary_search(int *arr, int start, int end, int target)
{
  while (start <= end)
  {
    int mid = start + (end - start) / 2;

    if (target < arr[mid])
      end = mid - 1;
    else if (target > arr[mid])
      start = mid + 1;
    else
      return mid;
  }

  return -1;
}

int find_peak(int *arr, int length)
{
  int start = 0;
  int end = length - 1;
  int peak = -1;

  while (start < end)
  {
    int mid = start + (end - start) / 2;
    if (mid > start && arr[mid] < arr[mid - 1])
    {
      peak = mid;
      break;
    }
    else if (mid < end && arr[mid] > arr[mid + 1])
    {
      peak = mid + 1;
      break;
    }

    if (arr[mid] > arr[start] && arr[mid] > arr[end])
      start = mid + 1;
    else
      end = mid - 1;
  }

  return peak;
}

int search_in_rotated_sorted(int *arr, int length, int target)
{
  if (length == 0)
    return -1;

  int peak = find_peak(arr, length);

  // if array is not rotated
  if (length == 1 || peak == -1)
    return binary_search(arr, 0, length - 1, target);

  int result = binary_search(arr, 0, peak - 1, target);
  if (result == -1)
    result = binary_search(arr, peak, length - 1, target);

  return result;
}

int main()
{
  int nums[] = {3, 4, 5, 6, 7, 0, 1, 2};
  cout << search_in_rotated_sorted(nums, 8, 4) << endl;

  int nums2[] = {3, 1};
  cout << search_in_rotated_sorted(nums2, 2, 1) << endl;

  return 0;
}
