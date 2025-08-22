#include "../graph.hpp"
#include <set>
#include <queue>

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

  WeightedGraphAdjacencyList<int> g2;
  g2.add_edge(0, 1, 1);
  g2.add_edge(1, 2, 2);
  g2.add_edge(0, 2, 3);
  map<int, vector<pair<int, int>> *> &graph2 = g2.get_graph();
  cout << "PRIMS (triangle): expected '3', received '" << prims_mst(graph2) << "'\n";

  WeightedGraphAdjacencyList<int> g3;
  g3.add_edge(0, 1, 1);
  g3.add_edge(1, 2, 2);
  g3.add_edge(2, 3, 1);
  g3.add_edge(3, 0, 2);
  g3.add_edge(0, 2, 2);
  g3.add_edge(1, 3, 3);
  map<int, vector<pair<int, int>> *> &graph3 = g3.get_graph();
  cout << "PRIMS (square): expected '4', received '" << prims_mst(graph3) << "'\n";

  WeightedGraphAdjacencyList<int> g4;
  g4.add_edge(0, 1, 5);
  g4.add_edge(2, 3, 7);
  map<int, vector<pair<int, int>> *> &graph4 = g4.get_graph();
  cout << "PRIMS (disconnected): expected '5', received '" << prims_mst(graph4) << "'\n";

  WeightedGraphAdjacencyList<int> g5;
  g5.add_edge(0, 1, 4);
  g5.add_edge(0, 7, 8);
  g5.add_edge(1, 2, 8);
  g5.add_edge(1, 7, 11);
  g5.add_edge(2, 3, 7);
  g5.add_edge(2, 8, 2);
  g5.add_edge(2, 5, 4);
  g5.add_edge(3, 4, 9);
  g5.add_edge(3, 5, 14);
  g5.add_edge(4, 5, 10);
  g5.add_edge(5, 6, 2);
  g5.add_edge(6, 7, 1);
  g5.add_edge(6, 8, 6);
  g5.add_edge(7, 8, 7);
  map<int, vector<pair<int, int>> *> &graph5 = g5.get_graph();
  cout << "PRIMS (complex): expected '37', received '" << prims_mst(graph5) << "'\n";

  return 0;
}
