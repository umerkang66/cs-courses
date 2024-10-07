#include <iostream>
using namespace std;

int sum(int *arr, int length)
{
  int sum = 0;
  for (int i = 0; i < length; i++)
    sum += arr[i];
  return sum;
}

int get_max(int *arr, int length)
{
  int max_el = INT32_MIN;
  for (int i = 0; i < length; i++)
    max_el = max(max_el, arr[i]);
  return max_el;
}

bool is_valid(int *boards, int length, int painters, int mid)
{
  int curr_painters = 0;
  int curr_boards = 0;

  for (int i = 0; i < length; i++)
  {
    if (boards[i] > mid)
      return false;

    if (curr_boards + boards[i] > mid)
    {
      curr_painters++;
      curr_boards = boards[i];
    }
    else
      curr_boards += boards[i];
  }

  return curr_painters <= painters;
}

int painters_partition(int *boards, int length, int painters)
{
  int start = get_max(boards, length);
  int end = sum(boards, length);
  int ans = -1;

  while (start <= end)
  {
    int mid = start + (end - start) / 2;

    if (is_valid(boards, length, painters, mid))
    {
      // solution is found
      ans = mid;
      // but be greedy
      end = mid - 1;
    }
    else
    {
      // this (mid) length is not enough to allocate all the painters, increase the length
      start = mid + 1;
    }
  }

  return ans;
}

int main()
{
  int boards[] = {11, 8, 12, 22, 21};
  int length = sizeof(boards) / sizeof(boards[0]);

  cout << painters_partition(boards, length, 2) << endl;
  return 0;
}
