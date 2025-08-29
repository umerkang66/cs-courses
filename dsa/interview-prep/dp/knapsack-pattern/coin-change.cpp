// https://leetcode.com/problems/coin-change/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
  // Function to find the minimum number of coins needed to make up the given amount
  // Returns -1 if it's not possible to make the amount with given coins
  int coinChange(vector<int> &coins, int amount)
  {
    // dp[i] represents minimum coins needed to make amount i
    // Initialize with amount+1 as it's greater than maximum possible coins needed
    vector<int> dp(amount + 1, amount + 1);
    // Base case: 0 coins needed to make amount 0
    dp[0] = 0;

    // Calculate minimum coins needed for each amount from 1 to target amount
    for (int i = 1; i <= amount; i++)
    {
      // Try each coin denomination
      for (int j = 0; j < coins.size(); j++)
      {
        int curr_amount = coins[j];
        // Check if we can use current coin (if remaining amount would be non-negative)
        if (i - curr_amount >= 0)
        {
          int exclude = dp[i];                   // Don't use current coin
          int include = 1 + dp[i - curr_amount]; // Use current coin + solution for remaining amount
          dp[i] = min(include, exclude);         // Take minimum of both choices
        }
      }
    }

    return dp[amount] == amount + 1 ? -1 : dp[amount];
  }
};

void test_case(vector<int> coins, int amount, int expected)
{
  Solution sol;
  int result = sol.coinChange(coins, amount);
  if (result == expected)
  {
    cout << "PASSED: ";
  }
  else
  {
    cout << "FAILED: ";
  }
  cout << "coins = {";
  for (size_t i = 0; i < coins.size(); ++i)
  {
    cout << coins[i];
    if (i + 1 < coins.size())
      cout << ", ";
  }
  cout << "}, amount = " << amount << ", expected = " << expected << ", got = " << result << endl;
}

int main()
{
  test_case({1, 2, 5}, 11, 3);              // 11 = 5 + 5 + 1
  test_case({2}, 3, -1);                    // Not possible
  test_case({1}, 0, 0);                     // Zero amount
  test_case({1}, 2, 2);                     // 2 = 1 + 1
  test_case({2, 5, 10, 1}, 27, 4);          // 10+10+5+2
  test_case({186, 419, 83, 408}, 6249, 20); // Large input
  test_case({2, 3, 7}, 12, 2);              // 12 = 7 + 5 (5 from 2+3)
  test_case({5, 7}, 1, -1);                 // Not possible
  test_case({3, 4, 5}, 7, 2);               // 3+4
  return 0;
}
