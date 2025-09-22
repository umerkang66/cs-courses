#include <bits/stdc++.h>
using namespace std;

class SegmentTree
{
  vector<int> tree;
  int n;

  void build_tree(vector<int> &nums, int start, int end, int node)
  {
    if (end - start == 0)
    {
      tree[node] = nums[start];
      return;
    }

    int mid = start + (end - start) / 2;

    int left = 2 * node + 1;
    int right = 2 * node + 2;
    build_tree(nums, start, mid, left);
    build_tree(nums, mid + 1, end, right);

    tree[node] = tree[left] + tree[right];
  }

public:
  // 2*n+1 | 4*n
  SegmentTree(vector<int> &nums)
  {
    n = nums.size();
    tree.resize(4 * n);
    build_tree(nums, 0, n - 1, 0);
  }

  int query(int q1, int q2)
  {
  }
};

int main()
{
  vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8};
  SegmentTree st(nums);

  cout << st.query(4, 6) << endl; // 5 + 6 + 7 = 18
  cout << st.query(0, 3) << endl; // 1 + 2 + 3 + 4 = 10
  cout << st.query(2, 5) << endl; // 3 + 4 + 5 + 6 = 18
  cout << st.query(0, 7) << endl; // 1+2+3+4+5+6+7+8 = 36
  cout << st.query(6, 6) << endl; // 7 (single element)
  return 0;
}
