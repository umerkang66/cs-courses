#include "./graph.hpp"

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

  graph.visualize();

  // start from 0
  graph.bfs(0);
  cout << endl;
  graph.dfs(0);

  return 0;
}
