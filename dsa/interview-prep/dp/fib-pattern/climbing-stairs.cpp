// https://leetcode.com/problems/climbing-stairs/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
  int helper_memo(int n, map<int, int> &m)
  {
    // if there is 1 stair, only 1 way to climb it
    // if there are 2 stairs, 2 ways to climb it, either 1 or 2 steps can be taken
    if (n == 1 || n == 2)
      return n;

    if (m[n])
      return m[n];

    m[n] = helper_memo(n - 1, m) + helper_memo(n - 2, m);
    return m[n];
  }

  int helper_tab(int n)
  {
    // if there is 1 stair, only 1 way to climb it
    // if there are 2 stairs, 2 ways to climb it, either 1 or 2 steps can be taken
    if (n == 1 || n == 2)
      return n;

    vector<int> v(n + 1);
    v[1] = 1;
    v[2] = 2;

    for (int i = 3; i <= n; i++)
      v[i] = v[i - 1] + v[i - 2];

    return v[n];
  }

  int climbStairs(int n)
  {
    map<int, int> m;
    int ans_memo = helper_memo(n, m);
    return helper_tab(n);
  }
};
