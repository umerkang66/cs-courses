// This C++ code implements a segment tree for efficient range sum queries.
#include <bits/stdc++.h>
using namespace std;

// The SegmentTree class provides a data structure for range queries.
class SegmentTree
{
  // The segment tree is stored in a vector.
  vector<int> tree;
  // The size of the input array.
  int n;

  // A recursive function to build the segment tree.
  // nums: the input array
  // start, end: the current segment's range
  // node: the current node's index in the tree vector
  void build_tree(vector<int> &nums, int start, int end, int node)
  {
    // Base case: if the segment has only one element, store it in the tree.
    if (end - start == 0)
    {
      tree[node] = nums[start];
      return;
    }

    // Find the middle point to divide the segment into two halves.
    int mid = start + (end - start) / 2;

    // Recursively build the left and right subtrees.
    int left = 2 * node + 1;
    int right = 2 * node + 2;
    build_tree(nums, start, mid, left);
    build_tree(nums, mid + 1, end, right);

    // The value of the current node is the sum of its children.
    tree[node] = tree[left] + tree[right];
  }

  // A recursive function to find the sum of a given range.
  // q1, q2: the query range
  // start, end: the current segment's range
  // node: the current node's index in the tree vector
  int range_sum(int q1, int q2, int start, int end, int node)
  {
    // Case 1: No overlap between the query range and the current segment.
    if (q2 < start || q1 > end)
      return 0;

    // Case 2: Complete overlap - the current segment is entirely within the query range.
    if (q1 <= start && q2 >= end)
      return tree[node];

    // Case 3: Partial overlap - the query range partially overlaps with the current segment.
    int mid = start + (end - start) / 2;

    // Recursively search in the left and right children and return the sum.
    int left_sum = range_sum(q1, q2, start, mid, 2 * node + 1);
    int right_sum = range_sum(q1, q2, mid + 1, end, 2 * node + 2);
    return left_sum + right_sum;
  }

  void update_tree(int index, int new_value, int start, int end, int node)
  {
    if (end - start == 0)
    {
      if (start == index)
        tree[node] = new_value;
      return;
    }

    int mid = start + (end - start) / 2;

    int left = 2 * node + 1;
    int right = 2 * node + 2;

    if (index <= mid)
      update_tree(index, new_value, start, mid, left);
    else
      update_tree(index, new_value, mid + 1, end, right);

    tree[node] = tree[left] + tree[right];
  }

public:
  // Constructor for the SegmentTree.
  // It initializes the tree with the given numbers.
  // The size of the tree vector is typically 4*n to be safe.
  SegmentTree(vector<int> &nums)
  {
    n = nums.size();
    tree.resize(4 * n);
    build_tree(nums, 0, n - 1, 0);
  }

  // Public function to perform a range sum query.
  int query(int q1, int q2) { return range_sum(q1, q2, 0, n - 1, 0); }

  void update(int index, int new_value) { update_tree(index, new_value, 0, n - 1, 0); }
};

int main()
{
  // Example usage of the SegmentTree.
  vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8};
  SegmentTree st(nums);

  // Initial queries
  cout << "Initial queries:" << endl;
  cout << st.query(4, 6) << " (expected 18)" << endl; // 5+6+7
  cout << st.query(0, 3) << " (expected 10)" << endl; // 1+2+3+4
  cout << st.query(2, 5) << " (expected 18)" << endl; // 3+4+5+6
  cout << st.query(0, 7) << " (expected 36)" << endl; // 1+2+3+4+5+6+7+8
  cout << st.query(6, 6) << " (expected 7)" << endl;  // single element

  cout << "\nAfter updates:" << endl;

  // Update index 4 (value 5 -> 10)
  st.update(4, 10);
  cout << st.query(4, 6) << " (expected 23)" << endl; // 10+6+7
  cout << st.query(0, 7) << " (expected 41)" << endl; // total sum increases by +5

  // Update index 0 (value 1 -> -1)
  st.update(0, -1);
  cout << st.query(0, 3) << " (expected 8)" << endl;  // -1+2+3+4
  cout << st.query(0, 7) << " (expected 39)" << endl; // total sum decreases by 2

  // Update index 7 (value 8 -> 0)
  st.update(7, 0);
  cout << st.query(6, 7) << " (expected 7)" << endl;  // 7+0
  cout << st.query(0, 7) << " (expected 31)" << endl; // total sum decreases by 8

  return 0;
}
