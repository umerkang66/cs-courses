// https://www.naukri.com/code360/problems/longest-subarray-zero-sum_757507

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

void largest_subarray_with_sum_zero(vector<int> &nums)
{
  unordered_map<int, int> m;

  int sum = 0;
  int ans = 0;

  for (int j = 0; j < nums.size(); j++)
  {
    sum += nums[j];
    if (sum == 0)
      ans = max(ans, j + 1);
    else if (m.count(sum))
    {
      int curr_len = j - m[sum];
      ans = max(curr_len, ans);
    }
    else
      m[sum] = j;
  }

  cout << ans << endl;
}

int main()
{
  // Test case 1: Mixed positive and negative numbers with zero sum
  vector<int> nums1 = {15, -2, 2, -8, 1, 7, 10};
  cout << "Expected: 5, Actual: ";
  largest_subarray_with_sum_zero(nums1); // Expected: 5

  return 0;
}
