#include <iostream>
using namespace std;

int *product_of_array_except_itself(int *nums, int length)
{
  int prefix[length];
  prefix[0] = 1;
  int suffix[length];
  suffix[length - 1] = 1;

  for (int i = 1; i < length; i++)
    prefix[i] = prefix[i - 1] * nums[i - 1];

  for (int i = length - 2; i >= 0; i--)
    suffix[i] = suffix[i + 1] * nums[i + 1];

  int *answers = new int[length];
  for (int i = 0; i < length; i++)
  {
    answers[i] = prefix[i] * suffix[i];
  }
  return answers;
}

// space complexity optimized
int *product_of_array_except_itself2(int *nums, int length)
{
  int *answers = new int[length];
  answers[0] = 1;

  for (int i = 1; i < length; i++)
  {
    answers[i] = answers[i - 1] * nums[i - 1];
  }

  int suffix = 1;
  for (int i = length - 2; i >= 0; i--)
  {
    suffix = (suffix * nums[i + 1]);
    answers[i] *= suffix;
  }

  return answers;
}

int main()
{
  int nums[] = {1, 2, 3, 4};
  int length = sizeof(nums) / sizeof(nums[0]);
  int *answer = product_of_array_except_itself(nums, length);
  int *answer2 = product_of_array_except_itself2(nums, length);

  for (int i = 0; i < length; i++)
    cout << nums[i] << ' ';
  cout << endl;
  for (int i = 0; i < length; i++)
    cout << answer[i] << ' ';
  cout << endl;
  for (int i = 0; i < length; i++)
    cout << answer2[i] << ' ';
  cout << endl;

  return 0;
}
