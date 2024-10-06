// https://leetcode.com/problems/best-time-to-buy-and-sell-stock

#include <iostream>
using namespace std;

int max_profit_in_stocks_BF(int *prices, int length)
{
  if (length <= 1)
  {
    return 0;
  }
  int best_buy[length];

  for (int i = 1; i < length; i++)
  {
    int curr_max = INT32_MIN;
    for (int j = i - 1; j >= 0; j--)
    {
      if (prices[i] - prices[j] > curr_max)
      {
        curr_max = prices[i] - prices[j];
        best_buy[i] = j;
      }
    }
  }

  int max_profit_combined = INT32_MIN;

  for (int i = 1; i < length; i++)
  {
    max_profit_combined = max(max_profit_combined, prices[i] - prices[best_buy[i]]);
  }

  return max_profit_combined < 0 ? 0 : max_profit_combined;
}

int max_profit_optimized(int *prices, int length)
{
  int max_profit = 0;
  int min_buy = prices[0];

  for (int i = 1; i < length; i++)
  {
    // calculate the min_buy price at the current selling day
    // we don't have to calculate the min from the start, because previous min is already the min of previous values, so just calculate min with the current value.
    min_buy = min(min_buy, prices[i]);
    int curr_profit = prices[i] - min_buy;
    max_profit = max(max_profit, curr_profit);
  }

  return max_profit;
}

int main()
{
  int stocks[] = {7, 1, 5, 3, 6, 4};
  int length = sizeof(stocks) / sizeof(stocks[0]);

  cout << max_profit_in_stocks_BF(stocks, length) << endl;
  cout << max_profit_optimized(stocks, length) << endl;

  return 0;
}
