#include "../graph.hpp"

/*
Logic for detecting a cycle in a directed graph:

1. Use Depth-First Search (DFS) to traverse the graph.
2. Maintain two maps:
  a. visited - to keep track of all visited nodes.
  b. recursionStack - to keep track of nodes in the current DFS path.
3. For each node, visit all its neighbors:
  a. If a neighbor has not been visited, recursively DFS on that neighbor.
  b. If a neighbor is visited and is also in the recursionStack, a cycle exists.
4. If DFS completes without finding such a condition, the graph does not contain a cycle.
*/

bool dir_cycle_helper(map<int, vector<int>> &graph, int start, map<int, bool> &visited, map<int, bool> &recursion_path)
{
  visited[start] = true;
  recursion_path[start] = true;

  for (const int &neighbor : graph[start])
  {
    if (!visited[neighbor])
    {
      if (dir_cycle_helper(graph, neighbor, visited, recursion_path))
        return true;
    }
    else
    {
      // if neighbor is visited and is not the parent of the current node, cycle does exist
      if (recursion_path[neighbor])
        return true;
    }
  }

  recursion_path[start] = false;
  return false;
}

bool detect_cycle_directed(map<int, vector<int>> &graph)
{
  map<int, bool> visited;
  map<int, bool> recursion_path;

  return dir_cycle_helper(graph, graph.begin()->first, visited, recursion_path);
}

int main()
{
  // Example 1: Has Cycle
  DirectedGraphAdjacencyList<int> graph;
  graph.add_edge(0, 1);
  graph.add_edge(0, 2);
  graph.add_edge(1, 2);
  graph.add_edge(2, 0); // this edge creates a cycle (0 -> 1 -> 2 -> 0)
  graph.add_edge(0, 3);
  graph.add_edge(3, 4);
  map<int, vector<int>> graph_list = graph.get_graph();
  cout << detect_cycle_directed(graph_list) << endl; // 1

  // Example 2: No Cycle
  DirectedGraphAdjacencyList<int> graph2;
  graph2.add_edge(0, 1);
  graph2.add_edge(0, 2);
  graph2.add_edge(0, 3);
  graph2.add_edge(3, 4);
  map<int, vector<int>> graph_list2 = graph2.get_graph();
  cout << detect_cycle_directed(graph_list2) << endl; // 0

  return 0;
}
