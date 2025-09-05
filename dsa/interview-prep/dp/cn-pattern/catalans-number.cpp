#include <bits/stdc++.h>
using namespace std;

/*
 * Catalan Numbers - Basic Recursive Implementation
 * Formula: C(n) = Σ(i=0 to n-1) C(i) * C(n-1-i)
 *
 * For each i from 0 to n-1:
 * - Left part uses i elements: C(i)
 * - Right part uses remaining n-1-i elements: C(n-1-i)
 * - Multiply and sum up all possibilities
 *
 * Time Complexity: O(4^n) - exponential due to overlapping subproblems
 * Space Complexity: O(n) - recursion stack depth
 */
int catalans(int n)
{
  if (n == 0 || n == 1) // Base cases: C(0) = C(1) = 1
    return 1;

  int ans = 0;
  for (int i = 0; i < n; i++)
    ans += catalans(i) * catalans(n - 1 - i); // Apply Catalan formula

  return ans;
}

/*
 * Memoized version of Catalan Numbers calculation
 * Uses Dynamic Programming to store intermediate results
 *
 * dp[n] stores the nth Catalan number
 * dp[n] = -1 indicates value not yet calculated
 *
 * Time Complexity: O(n^2) - each subproblem computed once
 * Space Complexity: O(n) - dp array + recursion stack
 */
int catalans_memo(int n, vector<int> &dp)
{
  if (n == 0 || n == 1) // Base cases
    return 1;

  if (dp[n] != -1) // Return if already calculated
    return dp[n];

  int ans = 0;
  for (int i = 0; i < n; i++)
    ans += catalans_memo(i, dp) * catalans_memo(n - 1 - i, dp);

  return dp[n] = ans; // Store and return result
}

/*
 * Tabulation (Bottom-up) approach for Catalan Numbers
 * Most efficient implementation as it:
 * 1. Avoids recursion overhead
 * 2. Calculates values in order, ensuring each value used is already computed
 * 3. Uses minimal space
 *
 * Time Complexity: O(n^2)
 * Space Complexity: O(n) for dp array
 */
int catalans_tab(int n)
{
  vector<int> dp(n + 1, 0);
  dp[0] = dp[1] = 1; // Initialize base cases

  for (int i = 2; i <= n; i++)
  {
    for (int j = 0; j < i; j++)
      // For each number j from 0 to i-1:
      // Left subtree: dp[j] possibilities
      // Right subtree: dp[i-1-j] possibilities
      dp[i] += dp[j] * dp[i - 1 - j];
  }

  return dp[n];
}

int main()
{
  int n = 5;
  vector<int> dp(n + 1, -1);
  cout << catalans(n) << endl;
  cout << catalans_memo(n, dp) << endl;
  cout << catalans_tab(n) << endl;

  return 0;
}
