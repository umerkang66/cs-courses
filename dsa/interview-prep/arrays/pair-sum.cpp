#include <iostream>
using namespace std;

int *pair_sum(int *arr, int length, int target)
{
  // left side elements are smaller, and right side elements are larger

  for (int i = 0, j = length - 1; i <= j; i++, j--)
  {
    if (arr[i] + arr[j] > target)
    {
      // make the result shorter, means move j pointer backwards
      j--;
    }
    else if (arr[i] + arr[j] < target)
    {
      // make the result larger, means move i pointer forwards
      i++;
    }
    else
    {
      return new int[2]{i, j};
    }
  }

  return new int[2]{-1, -1};
}

int main()
{
  // sorted
  int arr[] = {1, 2, 6, 7, 11, 15};
  int length = sizeof(arr) / sizeof(arr[0]);
  int *pair = pair_sum(arr, length, 9);
  cout << pair[0] << " " << pair[1] << endl;

  // sorted
  int arr2[] = {1, 2, 6, 7, 11, 15};
  int length2 = sizeof(arr2) / sizeof(arr2[0]);
  int *pair2 = pair_sum(arr2, length2, 10);
  cout << pair2[0] << " " << pair2[1] << endl;

  return 0;
}
