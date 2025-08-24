// https://leetcode.com/problems/redundant-connection/

#include <bits/stdc++.h>
using namespace std;

class DSU
{
  int n;
  vector<int> parent;
  vector<int> rank;

public:
  // Constructor: Initializes DSU for 'n' elements.
  // Each element is its own parent initially, and rank is set to 0.
  DSU(int n) : n(n), parent(n), rank(n)
  {
    for (int i = 0; i < n; i++)
    {
      parent[i] = i;
      rank[i] = 0;
    }
  }

  // Finds the representative (leader) of the set containing 'x'.
  // Uses path compression to flatten the structure for efficiency.
  int find(int x)
  {
    if (parent[x] == x)
      return x;
    return parent[x] = find(parent[x]); // path compression
  }

  // Unites the sets containing 'a' and 'b' using union by rank.
  // Attaches the tree with lower rank under the tree with higher rank.
  // If ranks are equal, makes one root and increments its rank.
  void union_by_rank(int a, int b)
  {
    int par_a = this->find(a);
    int par_b = this->find(b);

    if (rank[par_a] < rank[par_b])
      parent[par_a] = par_b;
    else if (rank[par_a] > rank[par_b])
      parent[par_b] = par_a;
    else // ranks are equal
    {
      parent[par_b] = par_a;
      rank[par_a]++;
      // means cycle exist
    }
  }

  bool cycle_exist(int a, int b)
  {
    int par_a = find(a);
    int par_b = find(b);

    return par_a == par_b;
  }

  // Prints the parent and rank of each element for debugging purposes.
  void get_info()
  {
    for (int i = 0; i < n; i++)
    {
      cout << i << ": " << parent[i] << " , " << rank[i] << endl;
    }
  }
};

class Solution
{
public:
  vector<int> findRedundantConnection(vector<vector<int>> &edges)
  {
    DSU dsu(edges.size() + 1);
    vector<int> answer(2, -1);

    for (int i = 0; i < edges.size(); i++)
    {
      auto &edge = edges[i];

      int u = edge[0];
      int v = edge[1];

      if (!dsu.cycle_exist(u, v))
        dsu.union_by_rank(u, v);
      else
      {
        answer[0] = u;
        answer[1] = v;
      }
    }

    return answer;
  }
};
