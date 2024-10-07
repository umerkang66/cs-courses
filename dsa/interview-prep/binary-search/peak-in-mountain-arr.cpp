// https://leetcode.com/problems/peak-index-in-a-mountain-array/

#include <iostream>
using namespace std;

int peak_index(int *arr, int length)
{
  int start = 1;
  int end = length - 2;

  while (start <= end)
  {
    int mid = start + (end - start) / 2;

    if (arr[mid] > arr[mid + 1] && arr[mid] > arr[mid - 1])
      return mid;

    // move to the left, we are on decreasing side
    else if (arr[mid] > arr[mid + 1])
      end = mid - 1;

    // move to the right, we are on increasing side
    else
      start = mid + 1;
  }

  return -1;
}

int main()
{
  // int arr[] = {0, 3, 8, 9, 5, 2};
  int arr[] = {24, 69, 100, 99, 79, 78, 67, 36, 26, 19};
  int length = sizeof(arr) / sizeof(arr[0]);
  cout << peak_index(arr, 6) << endl;

  return 0;
}
