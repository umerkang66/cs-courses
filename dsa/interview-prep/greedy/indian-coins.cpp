#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int minimum_coins(vector<int> coins, int total_amount)
{
  // just in case
  sort(coins.begin(), coins.end());

  int count = 0;

  for (int i = coins.size() - 1; i >= 0 && total_amount > 0; i--)
  {
    if (coins[i] <= total_amount)
    {
      count += total_amount / coins[i];
      total_amount = total_amount % coins[i];
    }
  }

  return count;
}

int main()
{
  vector<int> coins = {1, 2, 5, 10, 20, 50, 100, 500, 2000};

  cout << minimum_coins(coins, 121) << endl;
  cout << minimum_coins(coins, 590) << endl;

  vector<int> coins2 = {186, 419, 83, 408};
  cout << minimum_coins(coins2, 6249) << endl;

  return 0;
}
