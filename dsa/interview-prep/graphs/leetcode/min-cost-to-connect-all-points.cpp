#include <bits/stdc++.h>
using namespace std;

struct CustomCompare
{
  bool operator()(const pair<int, int> &a, const pair<int, int> &b)
  {
    return a.second > b.second;
  }
};

class Solution
{
public:
  int minCostConnectPoints(vector<vector<int>> &points)
  {
    int V = points.size();

    priority_queue<pair<int, int>, vector<pair<int, int>>, CustomCompare> q;

    vector<bool> mst(V, false);
    int total_cost = 0;

    q.push(make_pair(0, 0));

    while (!q.empty())
    {
      int u = q.top().first;
      int cost = q.top().second;
      q.pop();

      if (!mst[u])
      {
        mst[u] = true;
        total_cost += cost;

        for (int v = 0; v < V; v++)
        {
          if (u != v) // u -> v
          {
            int wt = abs(points[u][0] - points[v][0]) + abs(points[u][1] - points[v][1]);

            q.push(make_pair(v, wt));
          }
        }
      }
    }

    return total_cost;
  }
};
