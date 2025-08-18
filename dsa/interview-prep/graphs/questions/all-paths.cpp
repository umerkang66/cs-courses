#include "../graph.hpp"

void print_vector(const vector<int> &vec)
{
  for (const int &val : vec)
  {
    cout << val << " ";
  }
  cout << endl;
}

void all_paths(map<int, vector<int>> graph, int start, int end, map<int, bool> &visited, vector<int> &path)
{
  visited[start] = true;
  path.push_back(start);

  if (start == end)
    print_vector(path);
  else
  {
    for (const int &neighbor : graph[start])
    {
      if (!visited[neighbor])
        all_paths(graph, neighbor, end, visited, path);
    }
  }

  path.pop_back();
  visited[start] = false;
}

int main()
{
  // Create a directed graph with 5 vertices
  DirectedGraphAdjacencyList<int> g;

  cout << "Graph1: " << endl;

  // Add some edges (example)
  g.add_edge(0, 1);
  g.add_edge(0, 2);
  g.add_edge(1, 3);
  g.add_edge(2, 3);
  g.add_edge(3, 4);

  map<int, vector<int>> graph = g.get_graph();
  map<int, bool> visited;
  vector<int> path;
  all_paths(graph, 0, 4, visited, path);

  cout << "Graph2: " << endl;

  DirectedGraphAdjacencyList<int> g2;
  g2.add_edge(0, 1);
  g2.add_edge(0, 2);
  g2.add_edge(1, 3);
  g2.add_edge(2, 3);
  g2.add_edge(1, 2);
  g2.add_edge(2, 4);
  g2.add_edge(3, 4);

  map<int, vector<int>> graph2 = g2.get_graph();
  map<int, bool> visited2;
  vector<int> path2;
  all_paths(graph2, 0, 4, visited2, path2);

  return 0;
}
