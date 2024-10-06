#include <iostream>
using namespace std;

// O(n3)
int max_sub_array_sum_BF(int *arr, int length)
{
  int max_sum = INT32_MIN;

  for (int i = 0; i < length; i++)
  {
    for (int j = i; j < length; j++)
    {
      int curr_sum = 0;
      for (int k = i; k <= j; k++)
      {
        curr_sum += arr[k];
      }
      max_sum = max(max_sum, curr_sum);
    }
  }

  return max_sum;
}

// O(n2)
int max_sub_array_sum_optimized(int *arr, int length)
{
  int max_sum = INT32_MIN;

  for (int i = 0; i < length; i++)
  {
    int curr_sum = 0;
    for (int j = i; j < length; j++)
    {
      // don't need to calculate all the sums from the scratch, just calculate add the next one
      // because we already have the previous one (sum)
      curr_sum += arr[j];
      max_sum = max(max_sum, curr_sum);
    }
  }

  return max_sum;
}

// O(n)
int kadanes_algo(int *arr, int length)
{
  // ALGO: if the subarray sum is (-), reset it to zero, bcs by adding other number it will decrease the total sum, not decrease it
  int max_sum = INT32_MIN;
  int cur_sum = 0;

  for (int i = 0; i < length; i++)
  {
    cur_sum += arr[i];
    max_sum = max(max_sum, cur_sum);
    if (cur_sum < 0)
    {
      cur_sum = 0;
    }
  }

  return max_sum;
}

int main()
{
  int arr[] = {1, -2, 3, -4, 5};
  int length = 5;
  cout << max_sub_array_sum_BF(arr, length) << endl;
  cout << max_sub_array_sum_optimized(arr, length) << endl;
  cout << kadanes_algo(arr, length) << endl;

  int arr2[] = {3, -4, 5, 4, -1, 7, -8};
  length = 7;
  cout << max_sub_array_sum_BF(arr2, length) << endl;
  cout << max_sub_array_sum_optimized(arr2, length) << endl;
  cout << kadanes_algo(arr2, length) << endl;

  return 0;
}
