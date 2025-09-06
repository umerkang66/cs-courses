/*
 * Matrix Chain Multiplication (MCM) - Dynamic Programming
 * ===================================================
 * Problem:
 * Given a sequence of matrices, find the most efficient way to multiply these matrices together.
 * The problem is not to actually perform the multiplications, but merely to decide in which order
 * to perform the multiplications to minimize the number of operations.
 *
 * Key Points:
 * 1. Matrix multiplication is associative: (AB)C = A(BC), but the number of operations differs
 * 2. For matrices of dimensions: (p×q) * (q×r), the cost is p*q*r operations
 * 3. Input array [40,20,30,10,30] represents matrices of dimensions:
 *    - A1: 40×20
 *    - A2: 20×30
 *    - A3: 30×10
 *    - A4: 10×30
 *
 * Solution Approaches:
 * 1. Memoization (Top-Down) [Current Implementation]:
 *    - Use recursive calls with memoization to solve subproblems
 *    - Fill dp table on-demand as recursive calls are made
 *    - Base case: single matrix (start == end)
 *    - Easier to implement but has recursive stack overhead
 *
 * 2. Tabulation (Bottom-Up) Alternative:
 *    - Fill dp table iteratively from smaller to larger subproblems
 *    - dp[i][j] represents min operations for matrices i to j
 *    - Outer loop: chain length (L) from 2 to n
 *    - Inner loops:
 *      * i from 1 to n-L+1 (start of chain)
 *      * j = i+L-1 (end of chain)
 *      * k from i to j-1 (partition point)
 *    - Formula: dp[i][j] = min(dp[i][k] + dp[k+1][j] + arr[i-1]*arr[k]*arr[j])
 *    - No recursion overhead, potentially faster in practice
 *
 * Both approaches have:
 * - Time Complexity: O(n^3)
 * - Space Complexity: O(n^2)
 *
 * Base Cases:
 * - Memoization: If start == end: Cost is 0 (single matrix)
 * - Tabulation: dp[i][i] = 0 (diagonal elements, single matrices)
 */

#include <bits/stdc++.h>
using namespace std;

/*
 * Helper function implementing the bottom-up (tabulation) approach for Matrix Chain Multiplication
 * @param arr: Array containing dimensions of matrices
 * @return: Minimum number of operations needed
 *
 * Implementation Details:
 * 1. dp[i][j] represents minimum operations needed to multiply matrices from index i to j
 * 2. We fill the table diagonally, starting from chain length 2 up to n-1
 * 3. For each cell dp[i][j], we try all possible partition points k between i and j
 *
 * Visual representation of dp table filling order (for n=4):
 * [0 1 2 3]  Numbers represent the order of filling
 * [- 0 1 2]  '-' means not used (i > j cases)
 * [- - 0 1]  '0' means diagonal (base case, single matrix)
 * [- - - 0]
 */
int helper_tab(const vector<int> &arr)
{
  int N = arr.size();

  // Create and initialize dp table
  // dp[i][j] will store minimum operations needed for matrices i to j
  vector<vector<int>> dp(N, vector<int>(N, 0));

  // Base case: single matrix requires 0 operations
  // Initialize diagonal elements to 0
  for (int i = 1; i < N; i++)
    dp[i][i] = 0;

  // Outer loop: chain length
  // We start with length 2 and go up to N-1
  for (int len = 2; len < N; len++)
  {
    // Inner loop: starting point of the chain
    // For each length, we try all possible starting points
    for (int i = 1; i <= N - len; i++)
    {
      // Calculate ending point based on current length
      int j = i + len - 1;
      dp[i][j] = INT_MAX;

      // Try all possible partition points between i and j
      for (int k = i; k < j; k++)
      {
        // Cost calculation:
        // 1. left_cost: minimum operations for matrices i to k
        int left_cost = dp[i][k];

        // 2. right_cost: minimum operations for matrices k+1 to j
        int right_cost = dp[k + 1][j];

        // 3. curr_cost: cost to multiply the resulting matrices
        // For matrices of dim (p×q) and (q×r), cost = p*q*r
        // Here: p = arr[i-1], q = arr[k], r = arr[j]
        int curr_cost = arr[i - 1] * arr[k] * arr[j];

        // Total cost for this partition
        int total_cost = left_cost + right_cost + curr_cost;

        // Update minimum cost if this partition gives better result
        dp[i][j] = min(dp[i][j], total_cost);
      }
    }
  }

  // Return minimum operations needed for entire chain (from index 1 to N-1)
  return dp[1][N - 1];
}

int helper_rec(const vector<int> &arr, int start, int end, vector<vector<int>> &dp)
{
  if (start == end)
    return 0;

  if (dp[start][end] != -1)
    return dp[start][end];

  int ans = INT_MAX;

  for (int k = start; k < end; k++)
  {
    // Total cost = Cost of left partition + Cost of right partition +
    // Cost of multiplying the two resultant matrices
    // For matrices (p×q) * (q×r), cost = p*q*r
    // Here: p = arr[start-1], q = arr[k], r = arr[end]
    int left_cost = helper_rec(arr, start, k, dp);
    int right_cost = helper_rec(arr, k + 1, end, dp);

    // Calculates the cost of multiplying two matrices in the matrix chain multiplication problem.
    // The cost is determined by the number of scalar multiplications required when multiplying
    // matrices with dimensions arr[start-1] x arr[k] and arr[k] x arr[end].
    int current_cost = arr[start - 1] * arr[k] * arr[end];
    int cost = left_cost + right_cost + current_cost;

    ans = min(ans, cost);
  }

  return dp[start][end] = ans;
}

int matrixMultiplication(const vector<int> &arr, int N)
{
  // Initialize DP table with -1 (uncomputed values)
  vector<vector<int>> dp(N, vector<int>(N, -1));
  // Start recursive computation from index 1 to N-1
  // Note: We start from 1 because arr[i-1] and arr[i] represent dimensions of matrix i
  // return helper_rec(arr, 1, N - 1, dp);
  return helper_tab(arr);
}

void runTest(const vector<int> &arr, int expected)
{
  int result = matrixMultiplication(arr, arr.size());
  cout << (result == expected ? "true" : "false")
       << " | Expected: " << expected
       << ", Got: " << result << endl;
}

int main()
{
  // Test Case 1: Four matrices with optimal grouping (A1 x (A2 x A3)) x A4
  // Matrices: 40×20, 20×30, 30×10, 10×30
  // Total operations: 26000
  runTest({40, 20, 30, 10, 30}, 26000);

  // Test Case 2: Four matrices with optimal grouping ((A1 x A2) x A3) x A4
  // Matrices: 10×20, 20×30, 30×40, 40×30
  // Total operations: 30000
  runTest({10, 20, 30, 40, 30}, 30000);

  // Test Case 3: Two matrices - only one possible way to multiply
  // Matrices: 10×20, 20×30
  // Total operations: 6000
  runTest({10, 20, 30}, 6000);

  // Test Case 4: Six matrices - complex example
  // Matrices: 5×10, 10×3, 3×12, 12×5, 5×50, 50×6
  // Total operations: 2010
  runTest({5, 10, 3, 12, 5, 50, 6}, 2010);

  // Test Case 5: Three matrices showing importance of parenthesization
  // Matrices: 1×2, 2×3, 3×4
  // (A1xA2)xA3 = 1*2*3 + 1*3*4 = 6 + 12 = 18
  // A1x(A2xA3) = 2*3*4 + 1*2*4 = 24 + 8 = 32
  // Optimal solution: 18 operations
  runTest({1, 2, 3, 4}, 18);

  return 0;
}
