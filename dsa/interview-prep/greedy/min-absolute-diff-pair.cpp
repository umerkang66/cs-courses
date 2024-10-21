// https://www.naukri.com/code360/problems/minimum-sum-of-absolute-difference_973294

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int min_absolute_diff(vector<int> &a, vector<int> &b)
{
  sort(a.begin(), a.end());
  sort(b.begin(), b.end());

  int total_absolute_diff = 0;

  for (int i = 0; i < a.size(); i++)
    total_absolute_diff += abs(a[i] - b[i]);

  return total_absolute_diff;
}

int main()
{
  vector<int> a = {4, 1, 8, 7};
  vector<int> b = {2, 3, 6, 5};

  int ans = min_absolute_diff(a, b);

  cout << ans << endl;

  return 0;
}
