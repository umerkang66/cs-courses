// https://leetcode.com/problems/longest-common-subsequence/

#include <iostream>
#include <vector>
using namespace std;

/**
 * Solution class containing methods to solve the Longest Common Subsequence problem
 * LCS is a sequence that appears in the same relative order in both strings,
 * but not necessarily contiguous
 */
class Solution
{
public:
  /**
   * Bottom-up tabulation approach to find the length of LCS
   * Time Complexity: O(n*m), Space Complexity: O(n*m)
   * where n and m are lengths of the input strings
   */
  int helper_tab(string &text1, string &text2)
  {
    // Initialize DP table with one extra row and column for base cases
    // when i==0 or j==0, LCS length is 0
    int n = text1.size(), m = text2.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    // Fill the DP table iteratively
    for (int i = 1; i <= n; i++)
    {
      for (int j = 1; j <= m; j++)
      {
        if (text1[i - 1] == text2[j - 1])
          // If characters match, add 1 to the LCS length from previous state
          dp[i][j] = 1 + dp[i - 1][j - 1];
        else
          // If characters don't match, take maximum of excluding either character
          dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
      }
    }

    // Return the length of LCS for the complete strings
    return dp[n][m];
  }

  /**
   * Top-down recursive approach with memoization to find the length of LCS
   * Time Complexity: O(n*m), Space Complexity: O(n*m)
   */
  int helper_rec(int i, int j, string &text1, string &text2, vector<vector<int>> &dp)
  {
    // Base case: if we reach end of either string, LCS length is 0
    if (i == text1.size() || j == text2.size())
      return 0;

    // If this subproblem is already solved, return the memoized result
    if (dp[i][j] != -1)
      return dp[i][j];

    if (text1[i] == text2[j])
      // If characters match, include this character in LCS and move both pointers
      dp[i][j] = helper_rec(i + 1, j + 1, text1, text2, dp) + 1;
    else
      // If characters don't match, try excluding either character and take maximum
      dp[i][j] = max(helper_rec(i + 1, j, text1, text2, dp), helper_rec(i, j + 1, text1, text2, dp));

    return dp[i][j];
  }

  int longestCommonSubsequence(string text1, string text2)
  {
    // Initialize memoization table with -1 (unused for tabulation approach)
    vector<vector<int>> dp(text1.size(), vector<int>(text2.size(), -1));
    return helper_rec(0, 0, text1, text2, dp); // Using tabulation approach
  }
};

int main()
{
  string text1, text2;
  int lcsLength;

  // Test Case 1: Basic example
  // Expected output: 3 (LCS is "ace")
  text1 = "abcde";
  text2 = "ace";

  auto sol = Solution();

  lcsLength = sol.longestCommonSubsequence(text1, text2);
  cout << "Test Case 1 - Length of LCS for '" << text1 << "' and '" << text2 << "': " << lcsLength << endl;

  // Test Case 2: More complex example
  // Expected output: 4 (LCS is "GTAB")
  text1 = "AGGTAB";
  text2 = "GXTXAYB";

  lcsLength = sol.longestCommonSubsequence(text1, text2);
  cout << "Test Case 2 - Length of LCS for '" << text1 << "' and '" << text2 << "': " << lcsLength << endl;

  return 0;
}
