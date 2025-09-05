/*
 * LeetCode 96: Unique Binary Search Trees
 * https://leetcode.com/problems/unique-binary-search-trees/
 *
 * Problem: Given n nodes labeled from 1 to n, count the number of structurally
 * unique BSTs (Binary Search Trees) that can store these numbers.
 *
 * This is a direct application of Catalan Numbers because:
 * 1. For each root i from 1 to n:
 *    - Numbers 1 to i-1 must go in left subtree
 *    - Numbers i+1 to n must go in right subtree
 * 2. Total arrangements = (left subtree arrangements) × (right subtree arrangements)
 * 3. Sum up arrangements for all possible roots
 */

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
  int helper_tab(int n)
  {
    vector<int> dp(n + 1, 0);
    dp[0] = 1;
    dp[1] = 1;

    for (int i = 2; i <= n; i++)
    {
      for (int j = 0; j < i; j++)
      {
        int left = dp[j];
        int right = dp[i - j - 1];
        dp[i] += left * right;
      }
    }

    return dp[n];
  }

  /*
   * Recursive solution with memoization
   * For each possible root from 1 to n:
   * - Left subtree uses numbers from 1 to root-1
   * - Right subtree uses numbers from root+1 to n
   * - Total arrangements = left_arrangements × right_arrangements
   *
   * Uses dp array to store computed results:
   * dp[i] = number of unique BSTs with i nodes
   * dp[i] = -1 means not yet computed
   *
   * Time: O(n^2) with memoization
   * Space: O(n) for dp array + recursion stack
   */
  int helper_rec(int n, vector<int> &dp)
  {
    if (n <= 1)
      return 1; // Empty tree or single node

    if (dp[n] != -1)
      return dp[n]; // Return cached result

    int result = 0;
    for (int root = 1; root <= n; root++)
    {
      // left subtree will contain numbers < i, so i-1
      int left = helper_rec(root - 1, dp);
      // right subtree will contain numbers > i, so n-i
      int right = helper_rec(n - root, dp);
      // this is catalan's formula
      result += left * right;
    }

    return dp[n] = result; // Cache and return result
  }

  /*
   * Main function that returns the number of unique BSTs
   * Initializes dp array with -1 (not computed)
   * Can use either recursive or tabulation approach
   */
  int numTrees(int n)
  {
    vector<int> dp(n + 1, -1); // Initialize dp array for memoization
    // return helper_rec(n, dp); // Recursive with memoization
    return helper_tab(n); // Tabulation approach (more efficient)
  }
};

/*
 * Test cases with expected results
 * The results follow the Catalan number sequence:
 * n=1 -> 1  (only one possible arrangement)
 * n=2 -> 2  (root can be 1 or 2)
 * n=3 -> 5  (root can be 1,2,3 with different arrangements)
 * n=4 -> 14 (fourth Catalan number)
 * n=5 -> 42 (fifth Catalan number)
 */
int main()
{
  Solution sol;

  vector<int> testCases = {1, 2, 3, 4, 5};
  vector<int> expected = {1, 2, 5, 14, 42};

  for (size_t i = 0; i < testCases.size(); i++)
  {
    int n = testCases[i];
    int got = sol.numTrees(n);
    cout << "n = " << n
         << " | Got: " << got
         << " | Expected: " << expected[i] << endl;
  }

  return 0;
}
