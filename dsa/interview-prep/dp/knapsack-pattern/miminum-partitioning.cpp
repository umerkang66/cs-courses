#include <bits/stdc++.h>
using namespace std;

/*
Problem: Minimum Difference Partition
- Given an array of integers, partition it into two subsets such that the absolute
  difference between their sums is minimum.
- This is a variation of the 0/1 Knapsack problem.

Key Insights:
1. If we can find one subset's sum (S1), the other subset's sum (S2) will be (Total_Sum - S1)
2. The minimum difference will be |S1 - S2| = |S1 - (Total_Sum - S1)|
3. To minimize this difference, S1 should be as close as possible to Total_Sum/2

Approach:
1. Calculate total sum of the array
2. Use DP to find subset sum closest to total_sum/2
3. Use 0/1 Knapsack pattern where:
   - Items are array elements
   - "Capacity" is total_sum/2
   - Goal is to maximize sum <= total_sum/2

Time Complexity:  O(n * sum), where n is array size and sum is total sum/2
Space Complexity: O(n * sum) for the DP table
*/

class Solution
{
public:
  int minimumDifference(vector<int> &nums)
  {
    // Calculate total sum of array and target sum (half of total)
    int total_sum = accumulate(nums.begin(), nums.end(), 0);
    int W = total_sum / 2; // Target sum for first subset
    int n = nums.size();

    // dp[i][j] represents the maximum sum we can get <= j using first i elements
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    // Fill DP table
    for (int i = 1; i <= n; i++) // For each element
    {
      for (int j = 1; j <= W; j++) // For each target sum
      {
        if (nums[i - 1] <= j) // If current element can be included
        {
          // Two choices for each element:
          // 1. Include current element
          int include = nums[i - 1] + dp[i - 1][j - nums[i - 1]];
          // 2. Exclude current element
          int exclude = dp[i - 1][j];

          // Take maximum of include and exclude
          dp[i][j] = max(include, exclude);
        }
        else // Current element is too large to include
          // Only choice is to exclude
          dp[i][j] = dp[i - 1][j];
      }
    }

    // dp[n][W] gives us the sum of first partition that's closest to total_sum/2
    int grp1Sum = dp[n][W];
    // Second partition sum is the remaining amount
    int grp2Sum = total_sum - dp[n][W];

    // Return absolute difference between the two partitions
    return abs(grp1Sum - grp2Sum);
  }
};

/*
Example walkthrough with array [1, 2, 3, 9]:
1. Total sum = 15, target for first partition (W) = 7
2. DP table will try to maximize sum <= 7
3. Final dp[n][W] = 6 (using elements 1,2,3)
4. Therefore: Partition1 = 6, Partition2 = 9
5. Minimum difference = |6-9| = 3
*/

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
