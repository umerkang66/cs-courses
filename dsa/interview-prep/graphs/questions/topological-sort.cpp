#include "../graph.hpp"
#include <stack>
#include <algorithm>

/**
 * Performs a topological sort on a directed acyclic graph (DAG).
 *
 * Topological sort is an algorithm that orders the vertices of a directed acyclic graph
 * such that for every directed edge from vertex U to vertex V, U comes before V in the ordering.
 * This is commonly used in scenarios like task scheduling, resolving symbol dependencies in linkers,
 * and determining the order of compilation tasks.
 */

void topological_sort_dfs(map<int, vector<int>> graph, int start, map<int, bool> &visited, stack<int> &s)
{
  visited[start] = true;

  for (const int &neighbor : graph[start])
  {
    if (!visited[neighbor])
      topological_sort_dfs(graph, neighbor, visited, s);
  }

  s.push(start);
}

int main()
{
  DirectedGraphAdjacencyList<int> g;

  g.add_edge(5, 0);
  g.add_edge(5, 2);
  g.add_edge(2, 3);
  g.add_edge(3, 1);
  g.add_edge(4, 1);
  g.add_edge(4, 0);

  map<int, vector<int>> graph_map = g.get_graph();
  stack<int> s;
  map<int, bool> visited;

  for (const auto &element : graph_map)
  {
    if (!visited[element.first])
      topological_sort_dfs(graph_map, element.first, visited, s);
  }

  while (!s.empty())
  {
    cout << s.top() << " ";
    s.pop();
  }
  cout << endl;
}
