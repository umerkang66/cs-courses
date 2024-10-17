// https://leetcode.com/problems/largest-rectangle-in-histogram

#include <iostream>
#include <stack>
using namespace std;

int *next_greater_left(int *heights, int n)
{
  stack<int> nsl_stack;
  nsl_stack.push(0);

  int *nsl = new int[n];
  for (int i = 0; i < n; i++)
    nsl[i] = -1;

  for (int i = 1; i < n; i++)
  {
    while (!nsl_stack.empty() && heights[nsl_stack.top()] >= heights[i])
      nsl_stack.pop();

    if (!nsl_stack.empty())
      nsl[i] = nsl_stack.top();

    nsl_stack.push(i);
  }

  return nsl;
}

int *next_greater_right(int *heights, int n)
{
  stack<int> nsr_stack;
  nsr_stack.push(n - 1);

  int *nsr = new int[n];
  // we are finding the width using the: right - left - 1 formula, so if there isn't any smaller element on the right, just set it to n, not -1, because all the next elements will be included
  for (int i = 0; i < n; i++)
    nsr[i] = n;

  for (int i = n - 2; i >= 0; i--)
  {
    while (!nsr_stack.empty() && heights[nsr_stack.top()] >= heights[i])
      nsr_stack.pop();

    if (!nsr_stack.empty())
      nsr[i] = nsr_stack.top();

    nsr_stack.push(i);
  }

  return nsr;
}

int max_area(int *heights, int n)
{
  int *nsl = next_greater_left(heights, n);
  int *nsr = next_greater_right(heights, n);
  int maxArea = INT32_MIN;

  for (int i = 0; i < n; i++)
  {
    int width = nsr[i] - nsl[i] - 1;
    int area = heights[i] * width;

    maxArea = max(area, maxArea);
  }

  return maxArea;
}

int main()
{
  int heights[] = {2, 1, 5, 6, 2, 3};

  cout << max_area(heights, sizeof(heights) / sizeof(heights[0])) << endl;

  return 0;
}
