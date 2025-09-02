// https://leetcode.com/problems/edit-distance/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
  int minDistance(string word1, string word2)
  {
    int m = word1.size();
    int n = word2.size();

    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    // if col is 0, means word2 == "", then to change from word1 to word2, we need the operations equal to the length of word1
    for (int i = 0; i <= m; i++)
      dp[i][0] = i; // delete operations
    // if row is 0, means word1 == "", then to change from word1 to word2, we need the operations equal to the length of word2
    for (int j = 0; j <= n; j++)
      dp[0][j] = j; // insert operations

    for (int i = 1; i <= m; i++)
    {
      for (int j = 1; j <= n; j++)
      {
        if (word1[i - 1] == word2[j - 1])
          dp[i][j] = 0 + dp[i - 1][j - 1];
        else
        {
          // we can insert, delete, replace

          // when we insert, in first word, its length remains the same, but word2 length decreases by 1
          int insert = dp[i][j - 1];

          // when we delete, in first word, its length decrease by 1 and word2 length remains the same, bcs we need to check the next word of word1 to the same word of word2
          int deleteO = dp[i - 1][j];

          // when we replace, after replacing, both words decrease by 1, bcs the required word is achieved, and now check the next one
          int replace = dp[i - 1][j - 1];

          dp[i][j] = 1 + min({insert, deleteO, replace});
        }
      }
    }

    return dp[m][n];
  }
};

int main()
{
  Solution sol;

  // Test case 1: Both strings are empty
  cout << sol.minDistance("", "") << " "; // Expected: 0

  // Test case 2: One string is empty
  cout << sol.minDistance("abc", "") << " "; // Expected: 3
  cout << sol.minDistance("", "abc") << " "; // Expected: 3

  // Test case 3: Both strings are the same
  cout << sol.minDistance("abc", "abc") << " "; // Expected: 0

  // Test case 4: One replacement needed
  cout << sol.minDistance("abc", "adc") << " "; // Expected: 1

  // Test case 5: Insertions and deletions
  cout << sol.minDistance("horse", "ros") << " "; // Expected: 3

  // Test case 6: Complex case
  cout << sol.minDistance("intention", "execution") << " "; // Expected: 5

  cout << endl;
  return 0;
}
