#include "../graph.hpp"
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

/*
  What is a Bipartite Graph?
  --------------------------
  A bipartite graph is a graph whose vertices can be divided into two disjoint and independent sets
  such that every edge connects a vertex in one set to a vertex in the other set. In other words,
  it is possible to color the graph's vertices using two colors such that no two adjacent vertices
  share the same color.

  Bipartite graphs do not contain any odd-length cycles.

  Algorithm Overview
  ------------------
  The algorithm implemented here uses Breadth-First Search (BFS) to check if the graph is bipartite:
    1. Start from any unvisited node and assign it a color (e.g., 0).
    2. For each node, assign the opposite color to all its unvisited neighbors.
    3. If a neighbor is already visited and has the same color as the current node, the graph is not bipartite.
    4. Repeat the process for all connected components of the graph.
    5. If no conflicts are found, the graph is bipartite.

  Notes:
    - The algorithm uses a queue for BFS traversal.
    - Colors are represented as integers (e.g., 0 and 1).
    - The function works for disconnected graphs by starting from the first node in the adjacency list.
    - The implementation assumes the graph is undirected.

  Usage:
    - The main function demonstrates usage with two example graphs: one bipartite and one not bipartite.
*/

bool isBipartite(GraphAdjacencyList<int> &graph)
{
  map<int, vector<int> *> my_graph = graph.get_graph();
  queue<int> q;

  map<int, int> colors; // 0 for blue, 1 for red, also use this for visited

  if (my_graph.empty())
    return true;
  int first = my_graph.begin()->first;

  q.push(first);
  colors[first] = 0;

  while (!q.empty())
  {
    int parent = q.front();
    q.pop();
    for (const int &neighbor : *my_graph[parent])
    {
      if (!colors[neighbor])
      {
        // if it is not visited
        colors[neighbor] = colors[parent] == 0 ? 1 : 0;
        q.push(neighbor);
      }
      else
      {
        // if it already visited
        if (colors[parent] == colors[neighbor])
          return false;
      }
    }
  }

  return true;
}

int main()
{
  GraphAdjacencyList<int> g;
  // Example: a simple undirected graph
  g.add_edge(1, 2);
  g.add_edge(2, 3);
  g.add_edge(3, 4);
  g.add_edge(4, 1);
  g.add_edge(4, 5);

  g.visualize();
  cout << endl;

  // Call bipartite check function
  bool result = isBipartite(g);
  cout << "Is bipartite: " << (result ? "Yes" : "No") << endl;

  cout << endl;

  GraphAdjacencyList<int> g2;
  // Create a triangle (3-cycle), which is not bipartite
  g2.add_edge(10, 11);
  g2.add_edge(11, 12);
  g2.add_edge(12, 10);

  g2.visualize();
  cout << endl;

  bool result2 = isBipartite(g2);
  cout << "Is bipartite: " << (result2 ? "Yes" : "No") << endl;
  return 0;
}
