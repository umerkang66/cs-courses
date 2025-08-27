// https://www.naukri.com/code360/problems/unbounded-knapsack_1215029

#include <iostream>
#include <vector>
using namespace std;

// Function to solve Unbounded Knapsack using Tabulation (Bottom-Up DP)
int unbounded_knapsack_tab(vector<int> &vals, vector<int> &weights, int W, int n)
{
  // Create a 2D DP table of size (n+1) x (W+1)
  // dp[i][j] represents the maximum value achievable using first i items and capacity j
  vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

  // Loop through items
  for (int i = 1; i <= n; i++)
  {
    // Loop through all capacities from 1 to W
    for (int j = 1; j <= W; j++)
    {
      // If the current item's weight is less than or equal to the current capacity `j`
      if (weights[i - 1] <= j)
        // Option 1: Include the item (stay on the same row to allow repetition of the same item)
        // Option 2: Exclude the item (take the value from the previous row)
        dp[i][j] = max(vals[i - 1] + dp[i][j - weights[i - 1]], dp[i - 1][j]);
      else
        // If the item's weight exceeds the current capacity, just exclude it
        dp[i][j] = dp[i - 1][j];
    }
  }

  // The answer will be in dp[n][W]: maximum value using n items and capacity W
  return dp[n][W];
}

int main()
{
  // Values (profits) of the items
  vector<int> vals = {15, 14, 10, 45, 30};
  // Weights corresponding to each item
  vector<int> weights = {2, 5, 1, 3, 4};
  // Maximum capacity of the knapsack
  int W = 7;
  // Total number of items
  int n = vals.size();

  // Call the function and print the maximum achievable value
  cout << unbounded_knapsack_tab(vals, weights, W, n) << endl;

  return 0;
}
