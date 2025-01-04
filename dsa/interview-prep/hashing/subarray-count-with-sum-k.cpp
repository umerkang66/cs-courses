// https://leetcode.com/problems/subarray-sum-equals-k/description/

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

void count_subarray_with_sum_k(vector<int> &nums, int k)
{
  unordered_map<int, int> m;

  int sum = 0;
  int count = 0;

  for (int j = 0; j < nums.size(); j++)
  {
    sum += nums[j];
    if (m.count(sum - k))
    {
      count += m[sum - k];
    }
    if (sum == k)
      count++;

    if (m.count(sum))
      m[sum]++;
    else
      m[sum] = 1;
  }

  cout << count << endl;
}

int main()
{
  // Test case 1: Mixed positive and negative numbers with zero sum
  vector<int> nums1 = {1, 2, 3};
  cout << "Expected: 2, Actual: ";
  count_subarray_with_sum_k(nums1, 3); // Expected: 5

  return 0;
}
