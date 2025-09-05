// https://leetcode.com/problems/wildcard-matching/description/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
  bool isMatch(string s, string p)
  {
    int m = s.size(), n = p.size();
    vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, 0));

    // initialization
    dp[0][0] = 1;
    for (int j = 1; j <= n; j++)
    {
      if (p[j - 1] == '*')
        // same solution as the previous last pattern character
        dp[0][j] = dp[0][j - 1];
      else // for '?' and any other char 'c'
        dp[0][j] = 0;
    }

    // 0 for if j==0, because if p is empty, nothing can be matched, expect for dp[0][0] that is already 1

    for (int i = 1; i <= m; i++)
    {
      for (int j = 1; j <= n; j++)
      {
        if (s[i - 1] == p[j - 1] || p[j - 1] == '?') // same // or p=?
          dp[i][j] = dp[i - 1][j - 1];

        else if (p[j - 1] == '*') // * cases
          // *, but previous are matching, so match * with ""
          // or just *
          // just choose which one is true
          dp[i][j] = dp[i][j - 1] || dp[i - 1][j];

        else // different
          dp[i][j] = 0;
      }
    }

    return dp[m][n];
  }
};

void test(const string &s, const string &p, bool expected)
{
  Solution sol;
  bool result = sol.isMatch(s, p);
  cout << "isMatch(\"" << s << "\", \"" << p << "\") = " << boolalpha << result
       << " | Expected: " << expected << endl;
}

int main()
{
  test("aa", "a", false);
  test("aa", "*", true);
  test("cb", "?a", false);
  test("adceb", "*a*b", true);
  test("acdcb", "a*c?b", false);
  test("", "*", true);
  test("", "?", false);
  test("abc", "abc", true);
  test("abc", "a*?", true);
  test("abc", "a*d", false);
  return 0;
}
