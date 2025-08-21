#include "../graph.hpp"

/**
 * Computes shortest paths from a source vertex to all other vertices in a weighted directed graph using the Bellman-Ford algorithm.
 *
 * The Bellman-Ford algorithm is capable of handling graphs with negative edge weights, as long as there are no negative weight cycles reachable from the source.
 * It works by relaxing all edges V-1 times, where V is the number of vertices in the graph. After these iterations, the shortest distances from the source to all other vertices are found.
 *
 * This implementation assumes the graph is represented as an adjacency list using a map from vertex id to a pointer to a vector of (neighbor, weight) pairs.
 *
 * @param source The starting vertex for shortest path calculations.
 * @param graph The weighted directed graph represented as a map from vertex id to a pointer to a vector of (neighbor, weight) pairs.
 *
 * @note
 * - If a vertex is unreachable from the source, its distance will remain as INT32_MAX (infinity).
 * - This implementation does not check for negative weight cycles.
 * - Time complexity: O(V * E), where V is the number of vertices and E is the number of edges.
 */
void bellman_ford(int source, map<int, vector<pair<int, int>> *> &graph)
{
  int V = graph.size();
  vector<int> distances(V, INT32_MAX);
  distances[source] = 0;

  // bellman ford always works by doing i v-1 times
  for (int i = 0; i < V - 1; i++)
  {
    for (int u = 0; u < V; u++)
    {
      for (auto &edge : *graph[u])
      {
        int v = edge.first;
        int w = edge.second;

        // only start from that u, that is 0, and not integer 32 max
        if (distances[u] != INT32_MAX)
          distances[v] = min(distances[v], distances[u] + w);
      }
    }
  }

  for (auto &node : graph)
  {
    int v = node.first;
    cout << "Shortest Distance from " << source << " to " << v << ": ";
    if (distances[v] == INT32_MAX)
      cout << "INF";
    else
      cout << distances[v];
    cout << endl;
  }
}

int main()
{
  WeightedDirectedGraphAdjacencyList<int> g;

  g.add_edge(0, 1, 2);
  g.add_edge(0, 2, 4);
  g.add_edge(1, 2, 1);
  g.add_edge(1, 3, 7);
  g.add_edge(2, 4, 3);
  g.add_edge(4, 3, 2);
  g.add_edge(3, 5, 1);
  g.add_edge(4, 5, 5);

  map<int, vector<pair<int, int>> *> graph = g.get_graph();

  bellman_ford(0, graph);
  cout << endl;
  bellman_ford(1, graph);
  cout << endl;
  bellman_ford(2, graph);

  return 0;
}
