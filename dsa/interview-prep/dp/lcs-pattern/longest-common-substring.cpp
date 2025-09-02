// https://www.naukri.com/code360/problems/longest-common-substring_1214702

#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
  int helper_tab(string &text1, string &text2)
  {
    int m = text1.size();
    int n = text2.size();
    // there is a high chance that an answer is not at the end
    int ans = 0;

    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= m; i++)
    {
      for (int j = 1; j <= n; j++)
      {
        if (text1[i - 1] == text2[j - 1])
          ans = max(ans, dp[i][j] = 1 + dp[i - 1][j - 1]);
        else
          dp[i][j] = 0;
      }
    }

    cout << "DP Table:" << endl;
    for (int i = 0; i <= m; i++)
    {
      for (int j = 0; j <= n; j++)
      {
        cout << dp[i][j] << " ";
      }
      cout << endl;
    }

    return ans;
  }

  int helper_rec(string &text1, string &text2, int i, int j, int count = 0)
  {
    if (i == 0 || j == 0)
      return count;

    if (text1[i - 1] == text2[j - 1])
      return helper_rec(text1, text2, i - 1, j - 1, count + 1);

    return max(count, max(helper_rec(text1, text2, i - 1, j, 0), helper_rec(text1, text2, i, j - 1, 0)));
  }

  int longestCommonSubstring(string text1, string text2)
  {
    vector<vector<int>> dp(text1.size() + 1, vector<int>(text2.size() + 1, -1));
    // return helper_rec(text1, text2, text1.size(), text2.size());
    return helper_tab(text1, text2);
  }
};

void test_longestCommonSubstring()
{
  Solution sol;

  cout << (sol.longestCommonSubstring("abcde", "abcde") == 5) << endl;
  cout << (sol.longestCommonSubstring("abc", "def") == 0) << endl;
  cout << (sol.longestCommonSubstring("abcdef", "zabcf") == 3) << endl;
  cout << (sol.longestCommonSubstring("a", "a") == 1) << endl;
  cout << (sol.longestCommonSubstring("", "abc") == 0) << endl;
  cout << (sol.longestCommonSubstring("abc", "") == 0) << endl;
  cout << (sol.longestCommonSubstring("xyzabc", "pqrabc") == 3) << endl;
  cout << (sol.longestCommonSubstring("abcxyz", "abcpqr") == 3) << endl;
  cout << (sol.longestCommonSubstring("abcde12345fghij", "12345xyzabcde") == 5) << endl;
}

int main()
{
  test_longestCommonSubstring();
  return 0;
}
