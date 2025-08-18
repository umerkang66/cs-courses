#include "../graph.hpp"
/*
Logic for detecting a cycle in an undirected graph:

1. Use Depth-First Search (DFS) to traverse the graph.
2. Maintain a visited map to keep track of visited nodes.
3. For each node, visit all its neighbors:
  a. If a neighbor has not been visited, recursively DFS on that neighbor.
  b. If a neighbor is visited and is not the parent of the current node, a cycle exists.
4. If DFS completes without finding such a condition, the graph does not contain a cycle.
*/

bool undir_cycle_helper(map<int, vector<int> *> &graph, int start, map<int, bool> &visited, int parent)
{
  visited[start] = true;

  for (const int &neighbor : *graph[start])
  {
    if (!visited[neighbor])
    {
      if (undir_cycle_helper(graph, neighbor, visited, start))
        return true;
    }
    else
    {
      // if neighbor is visited and is not the parent of the current node, cycle does exist
      if (neighbor != parent)
        return true;
    }
  }

  return false;
}

bool detect_cycle_undirected(map<int, vector<int> *> &graph)
{
  map<int, bool> visited;
  int parent = -1;

  return undir_cycle_helper(graph, graph.begin()->first, visited, parent);
}

int main()
{
  GraphAdjacencyList<int> graph;
  graph.add_edge(0, 1);
  graph.add_edge(0, 2);
  graph.add_edge(1, 2);
  graph.add_edge(0, 3);
  graph.add_edge(3, 4);
  map<int, vector<int> *> graph_list = graph.get_graph();
  cout << detect_cycle_undirected(graph_list) << endl; // 1

  GraphAdjacencyList<int> graph2;
  graph2.add_edge(0, 1);
  graph2.add_edge(0, 2);
  graph2.add_edge(0, 3);
  graph2.add_edge(3, 4);
  map<int, vector<int> *> graph_list2 = graph2.get_graph();
  cout << detect_cycle_undirected(graph_list2) << endl; // 0
}
