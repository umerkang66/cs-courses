// https://www.naukri.com/code360/library/subset-sum-problem

#include <bits/stdc++.h>
using namespace std;

bool subsetSumToK(int n, int k, vector<int> &arr)
{
  vector<vector<bool>> dp(n + 1, vector<bool>(k + 1, false));

  for (int i = 0; i <= n; i++)
    dp[i][0] = true;

  for (int i = 1; i <= n; i++)
  {
    for (int j = 1; j <= k; j++)
    {
      if (arr[i - 1] <= j)
      {
        // add it
        // the element that is added
        bool add = dp[i - 1][j - arr[i - 1]];
        // don't add it
        bool dontadd = dp[i - 1][j];

        dp[i][j] = dontadd || add;
      }
      // don't add it
      else
        dp[i][j] = dp[i - 1][j];
    }
  }

  return dp[n][k];
}

int main()
{
  vector<int> arr1 = {1, 2, 3, 4};
  int k1 = 5;
  cout << "yes:" << (subsetSumToK(arr1.size(), k1, arr1) ? "yes" : "no") << "\n";

  vector<int> arr2 = {2, 4, 6, 8};
  int k2 = 5;
  cout << "no:" << (subsetSumToK(arr2.size(), k2, arr2) ? "yes" : "no") << "\n";

  vector<int> arr3 = {3, 34, 4, 12, 5, 2};
  int k3 = 9;
  cout << "yes:" << (subsetSumToK(arr3.size(), k3, arr3) ? "yes" : "no") << "\n";

  vector<int> arr4 = {1, 2, 3};
  int k4 = 0;
  cout << "yes:" << (subsetSumToK(arr4.size(), k4, arr4) ? "yes" : "no") << "\n";

  vector<int> arr5 = {};
  int k5 = 1;
  cout << "no:" << (subsetSumToK(arr5.size(), k5, arr5) ? "yes" : "no") << "\n";

  return 0;
}
