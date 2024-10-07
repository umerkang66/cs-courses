#include <iostream>
#include <algorithm>
using namespace std;

int sum(int *arr, int length)
{
  int sum = 0;
  for (int i = 0; i < length; i++)
    sum += arr[i];
  return sum;
}

bool is_valid(int *stalls, int length, int cows, int min_allowed_distance)
{
  // place the first cow
  int curr_cows = 1;
  int last_cow_position = stalls[0];

  for (int i = 1; i < length; i++)
  {
    if (stalls[i] - last_cow_position >= min_allowed_distance)
    {
      curr_cows++;
      last_cow_position = stalls[i];
    }

    if (curr_cows == cows)
      return true;
  }

  return false;
}

int aggressive_cows(int *stalls, int length, int painters)
{
  sort(stalls, stalls + length);

  int start = 1;
  int end = stalls[length - 1] - stalls[0];
  int ans = -1;

  while (start <= end)
  {
    int mid = start + (end - start) / 2;

    if (is_valid(stalls, length, painters, mid))
    {
      // solution is found
      ans = mid;
      // but be greedy
      start = mid + 1;
    }
    else
    {
      // this (mid) min-distance is not enough to allocate all the cows, decrease the min-distance
      end = mid - 1;
    }
  }

  return ans;
}

// allocate the cows, such that minimum distance between them should be maximum
int main()
{
  int stalls[] = {1, 2, 8, 4, 9};
  int length = sizeof(stalls) / sizeof(stalls[0]);

  cout << aggressive_cows(stalls, length, 3) << endl;
  return 0;
}
