#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct Num
{
  int val, idx;
  Num(int val, int idx) : val(val), idx(idx) {}

  // this is make a max-heap
  bool operator<(const Num &obj) const
  {
    return this->val < obj.val;
  }
};

void sliding_window_max(vector<int> &nums, int k)
{
  if (k > nums.size())
    return;

  priority_queue<Num> pq;
  vector<int> ans;

  for (int i = 0; i < k; i++)
    pq.push(Num{nums[i], i});

  ans.push_back(pq.top().val);

  for (int i = k; i < nums.size(); i++)
  {
    // the current window has i-k+1 window elemnets
    while (!pq.empty() && pq.top().idx <= i - k)
    {
      pq.pop();
    }
    pq.push(Num{nums[i], i});
    ans.push_back(pq.top().val);
  }

  for (const int &num : ans)
    cout << num << ' ';
  cout << endl;
}

int main()
{
  vector<int> nums = {1, 3, -1, -3, 5, 3, 6, 7};
  sliding_window_max(nums, 3);

  return 0;
}
