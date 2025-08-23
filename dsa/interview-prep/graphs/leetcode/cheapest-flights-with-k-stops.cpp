// https://leetcode.com/problems/cheapest-flights-within-k-stops/

#include <bits/stdc++.h>
using namespace std;

struct NodeInfo
{
  int u;
  int cost;
  int stops;

  NodeInfo(int u_, int cost_, int stops_) : u(u_), cost(cost_), stops(stops_) {}
};

class Solution
{
public:
  int findCheapestPrice(int n, vector<vector<int>> &flights, int src, int dst, int k_p)
  {
    int total_cost = 0;
    vector<int> distances(n, INT32_MAX);
    queue<NodeInfo> q;

    q.push(NodeInfo(src, 0, -1));
    distances[src] = 0;

    while (!q.empty())
    {
      int u = q.front().u;
      int cost = q.front().cost;
      int k = q.front().stops;
      q.pop();

      for (int i = 0; i < flights.size(); i++)
      {
        if (flights[i][0] == u)
        {
          int v = flights[i][1];
          int current_cost = flights[i][2];
          int newk = k + 1;

          if (cost + current_cost < distances[v] && newk <= k_p)
          {
            distances[v] = cost + current_cost;
            q.push(NodeInfo(v, distances[v], newk));
          }
        }
      }
    }

    return distances[dst] == INT32_MAX ? -1 : distances[dst];
  }
};

int main()
{
  Solution sol;
  int n = 4;
  vector<vector<int>> flights = {
      {0, 1, 100},
      {1, 2, 100},
      {2, 3, 100},
      {0, 2, 500}};
  int src = 0;
  int dst = 3;
  int k = 1;
  int result = sol.findCheapestPrice(n, flights, src, dst, k);
  cout << "Cheapest price from " << src << " to " << dst << " with at most " << k << " stops is: " << result << endl;
  return 0;
}
