#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
  int minimumDifference(vector<int> &nums)
  {
    int total_sum = accumulate(nums.begin(), nums.end(), 0);
    int W = total_sum / 2;
    int n = nums.size();

    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    for (int i = 1; i <= n; i++)
    {
      for (int j = 1; j <= W; j++)
      {
        if (nums[i - 1] <= j)
        {
          // include
          int include = nums[i - 1] + dp[i - 1][j - nums[i - 1]];
          // exclude
          int exclude = dp[i - 1][j];

          dp[i][j] = max(include, exclude);
        }
        else
          // exclude
          dp[i][j] = dp[i - 1][j];
      }
    }

    int grp1Sum = dp[n][W];
    int grp2Sum = total_sum - dp[n][W];

    return abs(grp1Sum - grp2Sum);
  }
};

// Function to run a single test case
void runTestCase(vector<int> nums, int expected)
{
  Solution sol;
  int result = sol.minimumDifference(nums);
  cout << "Input: ";
  for (int x : nums)
    cout << x << " ";
  cout << "\nExpected: " << expected << ", Got: " << result
       << " -> " << (result == expected ? "PASS" : "FAIL") << "\n";
}

int main()
{
  // Test cases
  runTestCase({1, 2, 3, 9}, 3);    // Split into {1,2,3}=6 and {9}=9 → diff=3
  runTestCase({1, 2, 7}, 4);       // {1,2}=3 and {7}=7 → diff=4
  runTestCase({1, 6, 11, 5}, 1);   // {1,6,5}=12 and {11}=11 → diff=1
  runTestCase({3, 1, 4, 2, 2}, 0); // {3,2}=5 and {4,1}=5 → diff=0
  runTestCase({10}, 10);           // Only one element → diff=10
  runTestCase({}, 0);              // Empty array → diff=0
}
