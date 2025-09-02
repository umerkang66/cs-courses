// https://leetcode.com/problems/longest-increasing-subsequence/

#include <bits/stdc++.h>
#include <cassert>

using namespace std;

class Solution
{
public:
  vector<int> get_unique(vector<int> &nums)
  {
    set<int> uniqueSet(nums.begin(), nums.end());
    return vector<int>(uniqueSet.begin(), uniqueSet.end());
  }

  int lengthOfLIS(vector<int> &nums)
  {
    vector<int> unique_nums = get_unique(nums);
    sort(unique_nums.begin(), unique_nums.end());
    int m = nums.size();
    int n = unique_nums.size();

    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= m; i++)
    {
      for (int j = 1; j <= n; j++)
      {
        if (nums[i - 1] == unique_nums[j - 1])
          dp[i][j] = 1 + dp[i - 1][j - 1];
        else
          dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
      }
    }

    return dp[m][n];
  }
};

void test_lengthOfLIS()
{
  Solution sol;

  vector<int> nums1 = {10, 9, 2, 5, 3, 7, 101, 18};
  int expected1 = 4;
  assert(sol.lengthOfLIS(nums1) == expected1);
  cout << "Test case # 1 passed!\n";

  vector<int> nums2 = {0, 1, 0, 3, 2, 3};
  int expected2 = 4;
  assert(sol.lengthOfLIS(nums2) == expected2);
  cout << "Test case # 2 passed!\n";

  vector<int> nums3 = {7, 7, 7, 7, 7, 7, 7};
  int expected3 = 1;
  assert(sol.lengthOfLIS(nums3) == expected3);
  cout << "Test case # 3 passed!\n";
}

int main()
{
  test_lengthOfLIS();
  return 0;
}
