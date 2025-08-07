#include "./graph.hpp"

bool has_path(map<int, vector<int> *> &graph, int start, int end, map<int, bool> &visited)
{
  if (start == end)
    return true;

  if (!graph[start] || graph[start]->empty())
    return false;

  visited[start] = true;
  if (start == end)
    return true;

  // find in the next depth
  for (const int &neighbor : *(graph[start]))
  {
    if (visited[neighbor])
      continue;
    if (has_path(graph, neighbor, end, visited))
      return true;
  }

  return false;
}

int main()
{
  GraphAdjacencyList<int> graph;
  graph.add_edge(0, 1);
  graph.add_edge(0, 2);
  graph.add_edge(1, 3);
  graph.add_edge(2, 4);
  graph.add_edge(3, 4);
  graph.add_edge(3, 5);
  graph.add_edge(4, 5);
  graph.add_edge(5, 6);

  graph.add_edge(7, 8);

  map<int, vector<int> *> graph_list = graph.get_graph();
  map<int, bool> visited;
  map<int, bool> visited2;
  map<int, bool> visited3;

  cout << has_path(graph_list, 0, 0, visited) << endl;  // 1
  cout << has_path(graph_list, 0, 5, visited) << endl;  // 1
  cout << has_path(graph_list, 7, 8, visited2) << endl; // 1
  cout << has_path(graph_list, 1, 8, visited3) << endl; // 0
}
