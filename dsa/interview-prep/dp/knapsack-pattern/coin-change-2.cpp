// https://leetcode.com/problems/coin-change-ii/description/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
  // Function to find the total number of different ways to make up the amount
  // using the given coins (unlimited supply of each coin)
  int change(int amount, vector<int> &coins)
  {
    int n = coins.size();
    // dp[i][j] represents number of ways to make amount j using first i coins
    // Using unsigned int to handle large numbers
    vector<vector<unsigned int>> dp(n + 1, vector<unsigned int>(amount + 1, 0));

    // Base case: when amount is 0, there is exactly 1 way to make it (using no coins)
    // This is true regardless of how many coins we can use
    for (int i = 0; i <= n; i++)
      dp[i][0] = 1;

    // Fill the dp table
    for (int i = 1; i <= n; i++)
    {
      for (int j = 1; j <= amount; j++)
      {
        // If current coin's value is less than or equal to current amount
        if (coins[i - 1] <= j)
          // Two choices:
          // 1. Include current coin: dp[i][j - coins[i-1]] (use same coin index as we can reuse)
          // 2. Exclude current coin: dp[i-1][j] (move to next coin)
          dp[i][j] = dp[i][j - coins[i - 1]] + dp[i - 1][j];
        else
          // If coin value is greater than current amount
          // We can only exclude this coin
          dp[i][j] = dp[i - 1][j];
      }
    }

    return dp[n][amount];
  }
};

int main()
{
  Solution sol;

  // Test Case 1
  vector<int> coins1 = {
      2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 44, 46, 48, 50, 52, 54, 56, 58, 60, 62, 64, 66, 68, 70, 72, 74, 76, 78, 80, 82, 84, 86, 88, 90, 92, 94, 96, 98, 100, 102, 104, 106, 108, 110, 112, 114, 116, 118, 120, 122, 124, 126, 128, 130, 132, 134, 136, 138, 140, 142, 144, 146, 148, 150, 152, 154, 156, 158, 160, 162, 164, 166, 168, 170, 172, 174, 176, 178, 180, 182, 184, 186, 188, 190, 192, 194, 196, 198, 200, 202, 204, 206, 208, 210, 212, 214, 216, 218, 220, 222, 224, 226, 228, 230, 232, 234, 236, 238, 240, 242, 244, 246, 248, 250, 252, 254, 256, 258, 260, 262, 264, 266, 268, 270, 272, 274, 276, 278, 280, 282, 284, 286, 288, 290, 292, 294, 296, 298, 300, 302, 304, 306, 308, 310, 312, 314, 316, 318, 320, 322, 324, 326, 328, 330, 332, 334, 336, 338, 340, 342, 344, 346, 348, 350, 352, 354, 356, 358, 360, 362, 364, 366, 368, 370, 372, 374, 376, 378, 380, 382, 384, 386, 388, 390, 392, 394, 396, 398, 400, 402, 404, 406, 408, 410, 412, 414, 416, 418, 420, 422, 424, 426, 428, 430, 432, 434, 436, 438, 440, 442, 444, 446, 448, 450, 452, 454, 456, 458, 460, 462, 464, 466, 468, 470, 472, 474, 476, 478, 480, 482, 484, 486, 488, 490, 492, 494, 496, 498, 500, 502, 504, 506, 508, 510, 512, 514, 516, 518, 520, 522, 524, 526, 528, 530, 532, 534, 536, 538, 540, 542, 544, 546, 548, 550, 552, 554, 556, 558, 560, 562, 564, 566, 568, 570, 572, 574, 576, 578, 580, 582, 584, 586, 588, 780, 936, 1170, 1560, 2340, 4680};
  int amount1 = 4681;

  cout << sol.change(amount1, coins1) << endl;

  return 0;
}
