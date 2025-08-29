// https://www.naukri.com/code360/problems/rod-cutting-problem_800284

#include <bits/stdc++.h>
using namespace std;

/*
 * Rod Cutting Problem:
 * Given a rod of length 'n' and prices of rod pieces of different lengths from 1 to n,
 * find the maximum profit that can be obtained by cutting the rod into pieces.
 *
 * Example:
 * Rod length = 4
 * Prices: [1, 5, 8, 9] (price[i] is the price for a piece of length i+1)
 * Possible ways to cut: 4, 1+3, 2+2, 1+1+2, etc.
 */
int max_profit_rod_cutting(vector<int> &prices, int rod_length)
{
  // n is the number of different piece lengths available (1 to n)
  int n = prices.size();
  // dp[i][j] represents the maximum profit for rod length j using pieces of length 1 to i
  vector<vector<int>> dp(n + 1, vector<int>(rod_length + 1, 0));

  // iterate through all possible piece lengths
  for (int i = 1; i <= n; i++)
  {
    // iterate through all possible rod lengths from 1 to rod_length
    for (int j = 1; j <= rod_length; j++)
    {
      // if current piece length (i) is less than or equal to current rod length (j)
      // we can choose to either include or exclude this piece
      if (i <= j)
      {
        // exclude: use the best profit without using current piece length
        int exclude = dp[i - 1][j];
        // include: price of current piece + best profit for remaining length
        // we can reuse the same piece length (i) for remaining length, hence dp[i][j-i]
        int include = prices[i - 1] + dp[i][j - i];

        // take maximum of include and exclude cases
        dp[i][j] = max(include, exclude);
      }
      else
        // if piece length is greater than rod length, we can't use it
        dp[i][j] = dp[i - 1][j];
    }
  }

  // Print the DP table for visualization (optional)
  // Rows represent piece lengths (1 to n)
  // Columns represent rod lengths (1 to rod_length)
  for (int i = 0; i <= n; i++)
  {
    for (int j = 0; j <= rod_length; j++)
      cout << dp[i][j] << " ";
    cout << endl;
  }

  // Return the maximum profit possible for the given rod length
  // using all available piece lengths
  return dp[n][rod_length];
}

int main()
{
  // Example: Price array where price[i] represents the price of rod piece of length (i+1)
  vector<int> price = {1, 5, 8, 9, 10, 17, 17, 20};
  // Total length of the rod we want to cut
  int rod_length = 8;
  // Calculate the maximum profit
  int result = max_profit_rod_cutting(price, rod_length);
  cout << "Maximum profit for rod of length " << rod_length << " is: " << result << endl;
  return 0;
}
