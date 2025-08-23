#include <bits/stdc++.h>
#include "../graph.hpp"
#include "../disjoint-set.hpp"

/**
 * Implements Minimum Spanning Tree (MST) algorithms for undirected weighted graphs.
 *
 * Typical algorithms: Kruskal's and Prim's.
 * - Kruskal's: Greedy, sorts edges, uses union-find.
 * - Prim's: Greedy, grows MST from a starting node using a priority queue.
 *
 * @returns int the total cost
 * @param graph A reference to the adjacency list representation of the weighted undirected graph.
 */

struct CustomCompare
{
  bool operator()(const pair<int, int> &a, const pair<int, int> &b) const
  {
    // Min heap: smaller first element (weight) has higher priority
    return a.second > b.second;
  }
};

// we need to use the visited, because it is undirected, so technically can be infinite
int prims_mst(map<int, vector<pair<int, int>> *> &graph)
{
  set<int> visited;
  priority_queue<pair<int, int>, vector<pair<int, int>>, CustomCompare> q;
  int first = graph.begin()->first;

  int total_cost = 0;
  q.push(make_pair(first, 0));

  while (!q.empty())
  {
    pair<int, int> current = q.top();
    q.pop();

    if (visited.find(current.first) == visited.end())
    {
      total_cost += current.second;
      visited.insert(current.first);

      for (const auto &neighbor : *graph[current.first])
      {
        if (visited.find(neighbor.first) == visited.end())
        {
          q.push(make_pair(neighbor.first, neighbor.second));
        }
      }
    }
  }

  return total_cost;
}

struct Edge
{
  int u, v, wt;
  Edge(int u, int v, int wt) : u(u), v(v), wt(wt) {}
};

int kruskals_mst(map<int, vector<pair<int, int>> *> &graph)
{
  int total_cost = 0;

  // u v wt
  vector<Edge>
      edges;
  for (const auto &element : graph)
  {
    int u = element.first;

    for (const auto &neighbor : *element.second)
    {
      int v = neighbor.first;
      int wt = neighbor.second;

      edges.push_back(Edge(u, v, wt));
    }
  }

  sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b)
       { return a.wt < b.wt; });

  DSU dsu(graph.size());

  for (int i = 0; i < edges.size(); i++)
  {
    auto &edge = edges[i];
    int u = edge.u;
    int v = edge.v;
    int wt = edge.wt;

    int par_u = dsu.find(u);
    int par_v = dsu.find(v);

    // cycle doesnot exists
    if (par_u != par_v)
    {
      // we can also do par_u, par_v
      dsu.union_by_rank(u, v);
      total_cost += wt;
    }
  }

  return total_cost;
}

int main()
{
  WeightedGraphAdjacencyList<int> g;

  g.add_edge(0, 1, 10);
  g.add_edge(0, 3, 30);
  g.add_edge(0, 2, 15);
  g.add_edge(1, 3, 40);
  g.add_edge(0, 1, 10);
  g.add_edge(2, 3, 50);

  map<int, vector<pair<int, int>> *> &graph = g.get_graph();

  cout << "PRIMS: expected '55', received '" << prims_mst(graph) << "'\n";

  cout << "KRUSKALS: expected '55', received '" << kruskals_mst(graph) << "'\n";

  return 0;
}
