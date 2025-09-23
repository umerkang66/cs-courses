// https://leetcode.com/problems/trapping-rain-water

#include <iostream>
using namespace std;

int trapping_rain_water(int *bars, int n)
{
  int left_max[n];
  left_max[0] = -1;
  int right_max[n];
  right_max[n - 1] = -1;

  for (int i = 1; i < n; i++)
    left_max[i] = max(left_max[i - 1], bars[i - 1]);

  for (int i = n - 2; i >= 0; i--)
    right_max[i] = max(right_max[i + 1], bars[i + 1]);

  int total_water = 0;

  for (int i = 1; i < n - 1; i++)
  {
    if (left_max[i] > bars[i] && right_max[i] > bars[i])
    {
      int min_bar = min(left_max[i], right_max[i]);

      // because the width is 1
      total_water += (min_bar - bars[i]) * 1;
    }
  }

  return total_water;
}

int main()
{
  int height[] = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
  int length = sizeof(height) / sizeof(height[0]);

  cout << trapping_rain_water(height, length) << endl;

  return 0;
}
