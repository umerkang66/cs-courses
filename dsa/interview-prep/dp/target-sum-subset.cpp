// https://www.naukri.com/code360/library/subset-sum-problem
// This program solves the Subset Sum Problem using dynamic programming.
// It checks if there exists a subset in the array whose sum equals a target value `k`.

#include <bits/stdc++.h>
using namespace std;

// Approach 1: Boolean DP
// Function to check if there is a subset that sums up to `k`
bool subsetSumToK(int n, int k, vector<int> &arr)
{
  // Create a 2D DP table where:
  // dp[i][j] = true if we can make sum `j` using the first `i` elements
  vector<vector<bool>> dp(n + 1, vector<bool>(k + 1, false));

  // Base case: Sum = 0 is always possible with an empty subset
  for (int i = 0; i <= n; i++)
    dp[i][0] = true;

  // Fill the DP table
  for (int i = 1; i <= n; i++) // iterate through elements
  {
    for (int j = 1; j <= k; j++) // iterate through all sums from 1 to k
    {
      if (arr[i - 1] <= j) // if current element can be included
      {
        // Option 1: Include the element and check if remaining sum is possible
        bool add = dp[i - 1][j - arr[i - 1]];
        // Option 2: Exclude the element
        bool dontadd = dp[i - 1][j];

        // Either including or excluding makes sum possible
        dp[i][j] = dontadd || add;
      }
      else
      {
        // Cannot include current element, just copy the previous state
        dp[i][j] = dp[i - 1][j];
      }
    }
  }

  // Final answer: is sum `k` possible using all `n` elements
  return dp[n][k];
}

// Approach 2: Value-based DP
// Function to check if subset sum can exactly match `k` by building up sum values
bool subsetSumToK2(int n, int k, vector<int> &arr)
{
  // Create a DP table where:
  // dp[i][j] = maximum sum ≤ j that can be formed using first `i` elements
  vector<vector<int>> dp(n + 1, vector<int>(k + 1, 0));

  // Fill the DP table
  for (int i = 1; i <= n; i++) // iterate through elements
  {
    for (int j = 1; j <= k; j++) // iterate through sums from 1 to k
    {
      if (arr[i - 1] <= j) // if current element can be included
      {
        // Option 1: Exclude the element (previous sum remains)
        // Option 2: Include the element (add its value to sum achievable by remaining capacity)
        dp[i][j] = max(dp[i - 1][j], arr[i - 1] + dp[i - 1][j - arr[i - 1]]);
      }
      else
      {
        // Current element is too large, so we can't include it
        dp[i][j] = dp[i - 1][j];
      }
    }
  }

  // If the maximum achievable sum equals `k`, subset exists
  return dp[n][k] == k;
}

int main()
{
  // Test case
  vector<int> arr1 = {1, 2, 3, 4};
  int k1 = 5;

  // Call first approach (Boolean DP)
  cout << "yes:" << (subsetSumToK(arr1.size(), k1, arr1) ? "yes" : "no") << "\n";

  // Call second approach (Value-based DP)
  cout << "yes:" << (subsetSumToK2(arr1.size(), k1, arr1) ? "yes" : "no") << "\n";

  return 0;
}
