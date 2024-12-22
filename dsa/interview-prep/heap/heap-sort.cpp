#include <iostream>
#include <vector>
using namespace std;

void heapify(int i, vector<int> &arr, int n)
{
  int left_child = i * 2 + 1;
  int right_child = i * 2 + 2;

  int max_idx = i;

  if (left_child < n && arr[left_child] > arr[max_idx])
    max_idx = left_child;
  if (right_child < n && arr[right_child] > arr[max_idx])
    max_idx = right_child;

  if (max_idx != i)
  {
    // swap them
    swap(arr[i], arr[max_idx]);
    heapify(max_idx, arr, n);
  }
}

void heap_sort(vector<int> &arr)
{
  int n = arr.size();

  // from 0 to n/2-1 elements are non-leaf nodes
  // after there are leaf nodes, we only have to call heapify function on non-leaf nodes
  // because on leaf nodes there is nothing to compare bcs there are not left and right childs
  for (int i = n / 2 - 1; i >= 0; i--)
    heapify(i, arr, n);

  // STEPS OF HEAP_SORT AFTER HEAPIFYING THE ARR
  // 1: Swap the 0th element with (n-1)th element
  // 2: Then heapify the remaining arr elements from 0 to n-1-i, that is why we have passed the 'n' size as separate variable in the heapify function
  // 3: Don't include the element that is in sorted place

  for (int i = n - 1; i >= 0; i--)
  {
    swap(arr[0], arr[i]);
    heapify(0, arr, i);
  }
}

void print_vec(vector<int> arr)
{
  for (const int &n : arr)
    cout << n << ' ';
  cout << endl;
}

int main()
{
  vector<int> arr = {1, 4, 2, 5, 3};
  print_vec(arr);
  heap_sort(arr);
  print_vec(arr);
  return 0;
}
