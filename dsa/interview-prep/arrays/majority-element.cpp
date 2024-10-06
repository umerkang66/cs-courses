// moore's voting algo
// https://leetcode.com/problems/majority-element/description/

#include <iostream>
using namespace std;

// ALGORITHM: if frequency is 0, update the answer, if ans is equal to the current element
// increase the frequency, if ans is different from current element, decrease the frequency
// the element which is more than n/2 times the length will NOT have the frequency goes to 0, so the answer will not update.

int moore_algo(int *arr, int length)
{
  int freq = 0;
  int ans = -1;

  for (int i = 0; i < length; i++)
  {
    if (freq == 0)
      ans = arr[i];
    if (ans == arr[i])
      freq++;
    else
      freq--;
  }

  return ans;
}

int main()
{
  int nums[] = {1, 2, 2, 2, 2, 1, 1};
  cout << moore_algo(nums, 7) << endl;

  return 0;
}
