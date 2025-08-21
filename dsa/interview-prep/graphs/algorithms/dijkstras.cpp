#include "../graph.hpp"
using namespace std;

/**
 * Implements Dijkstra's algorithm for finding the shortest paths from a source node to all other nodes in a weighted directed graph.
 *
 * Dijkstra's algorithm is a classic algorithm used in graph theory to solve the single-source shortest path problem for graphs with non-negative edge weights.
 * It is widely used in network routing protocols, mapping applications, and various optimization problems where the shortest or least-cost path is required.
 *
 * Algorithm Overview:
 * 1. Initialize the distance to the source node as 0 and to all other nodes as infinity.
 * 2. Use a priority queue (min-heap) to repeatedly select the node with the smallest known distance.
 * 3. For the selected node, update the distances to its adjacent nodes if a shorter path is found.
 * 4. Repeat until all nodes have been visited or the shortest paths are determined.
 *
 * Typical Uses:
 * - GPS navigation systems to find the shortest driving route.
 * - Network routing (e.g., OSPF protocol).
 * - Pathfinding in games and robotics.
 *
 * @param graph A reference to the adjacency list representation of the weighted directed graph.
 */

struct CompareSecond
{
  bool operator()(const pair<int, int> &a, const pair<int, int> &b) { return a.second > b.second; } // minheap
};

// this is for DAG
void dijkstras(int source, map<int, vector<pair<int, int>> *> &graph)
{
  int n = graph.size();
  vector<int> distances(n, INT32_MAX);
  distances[source] = 0;

  // pair is for vertex and vertex distance
  priority_queue<pair<int, int>,
                 vector<pair<int, int>>,
                 CompareSecond>
      q;

  q.push(make_pair(source, 0));

  while (!q.empty())
  {
    pair<int, int> front = q.top();
    q.pop();

    int u = front.first;

    for (const auto &neighbor : *graph[u])
    {
      int v = neighbor.first;
      int w = neighbor.second;

      distances[v] = min(distances[v], distances[u] + w);

      // even if the distance is bigger, we can add it because, according to min heap
      // first one to run is the one with shorter distance, and when the bigger
      // arrives distance just don't update because we need the minimum one.
      q.push(make_pair(v, distances[v]));
    }
  }

  for (int i = 0; i < distances.size(); ++i)
  {
    cout << "Shortest Distance from " << source << " to " << i << ": ";
    if (distances[i] == INT32_MAX)
      cout << "INF";
    else
      cout << distances[i];
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

  dijkstras(0, graph);
  cout << endl;
  dijkstras(1, graph);

  return 0;
}
