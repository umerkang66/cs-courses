// https://www.naukri.com/code360/problems/connect-n-ropes-with-minimum-cost_625783

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int min_cost_by_connecting_ropes(vector<int> &ropes)
{
  // min-heap
  priority_queue<int, vector<int>, greater<int>> pq(ropes.begin(), ropes.end());

  int cost = 0;

  while (pq.size() != 1)
  {
    int first = pq.top();
    pq.pop();
    int second = pq.top();
    pq.pop();

    int ans = first + second;

    cost += ans;
    pq.push(ans);
  }

  return cost;
}

int main()
{
  vector<int> ropes = {4, 3, 2, 6};

  cout << min_cost_by_connecting_ropes(ropes) << endl;

  return 0;
}
