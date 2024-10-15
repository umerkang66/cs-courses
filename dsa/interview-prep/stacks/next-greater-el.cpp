#include <iostream>
#include <stack>
using namespace std;

int *next_greater(int *nums, int n)
{
  stack<int> s;
  s.push(nums[n - 1]);

  int *results = new int[n];
  for (int i = 0; i < n; i++)
    results[i] = -1;

  for (int i = n - 2; i >= 0; i--)
  {
    while (!s.empty() && s.top() <= nums[i])
      s.pop();

    // we haven't popped the one, that is greater, because it can also be a greater element for other previous elements
    if (!s.empty())
      results[i] = s.top();

    s.push(nums[i]);
  }

  return results;
}

int main()
{
  int nums[] = {6, 8, 0, 1, 3};
  int n = sizeof(nums) / sizeof(nums[0]);

  int *results = next_greater(nums, n);

  for (int i = 0; i < n; i++)
    cout << nums[i] << " ";
  cout << endl;

  for (int i = 0; i < n; i++)
    cout << results[i] << " ";
  cout << endl;

  delete[] results;

  return 0;
}
