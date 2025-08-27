// https://www.naukri.com/code360/problems/0-1-knapsack_1072980

#include <iostream>
#include <vector>
using namespace std;

int zero1_knapsack_rec(vector<int> &vals, vector<int> &weights, int W, int n, vector<vector<int>> &dp)
{
  if (W == 0 || n == 0)
    return 0;

  if (dp[n][W] != -1)
    return dp[n][W];

  int include = 0;

  if (weights[n - 1] <= W)
  {
    // add the current value to the returned value
    include = vals[n - 1] + zero1_knapsack_rec(vals, weights, W - weights[n - 1], n - 1, dp);
  }

  int exclude = zero1_knapsack_rec(vals, weights, W, n - 1, dp);

  dp[n][W] = max(include, exclude);
  return dp[n][W];
}

int zero1_knapsack_tab(vector<int> &vals, vector<int> &weights, int W, int n)
{
  // Base Case Initialization: n=0,W=0
  // when n==0, no matter what the W, max profit will be 0
  // when W==0, no matter what the n, max profit will be 0
  // I just shortened and initialize everything with 0
  vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

  for (int i = 1; i <= n; i++)
  {
    for (int j = 1; j <= W; j++)
    {
      if (weights[i - 1] <= j)
      {
        // exclude
        int exclude = dp[i - 1][j];

        // include
        // include current value + prevValue
        // prevValue = 1 item removed so (i-1)
        // and current weight removed (j-weights[i])
        int include = vals[i - 1] + dp[i - 1][j - weights[i - 1]];

        dp[i][j] = max(include, exclude);
      }
      // only exclude
      else
        dp[i][j] = dp[i - 1][j];
    }
  }

  return dp[n][W];
}

int main()
{
  vector<int> vals = {15, 14, 10, 45, 30};
  vector<int> weights = {2, 5, 1, 3, 4};
  // weight of sack
  int W = 7;
  int n = vals.size();

  vector<vector<int>> dp(n + 1, vector<int>(W + 1, -1));

  cout << zero1_knapsack_rec(vals, weights, W, n, dp) << endl;
  cout << zero1_knapsack_tab(vals, weights, W, n) << endl;

  return 0;
}
