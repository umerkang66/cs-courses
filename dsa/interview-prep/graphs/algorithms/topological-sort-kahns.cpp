#include "../graph.hpp"
#include <stack>
#include <queue>

/*
 * Function: topological_sort_kahns
 * --------------------------------
 * Performs topological sorting of a directed acyclic graph (DAG) using Kahn's Algorithm.
 *
 * Kahn's Algorithm is an iterative method for finding a topological ordering of the vertices in a DAG.
 * The algorithm works by repeatedly removing nodes with zero in-degree (no incoming edges) and adding
 * them to the topological order. For each removed node, it decrements the in-degree of its neighbors.
 * If a neighbor's in-degree becomes zero, it is added to the set of nodes to process next.
 *
 * This process continues until all nodes are processed or a cycle is detected (i.e., if there are still
 * nodes with non-zero in-degree after processing, the graph is not a DAG).
 *
 * Parameters:
 *   - graph: The adjacency list representation of the directed graph.
 *   - start: The starting node for the topological sort (not used in standard Kahn's algorithm, as it processes all nodes).
 *   - visited: A map to keep track of visited nodes.
 *   - s: A stack to store the topological order of nodes.
 *
 * Note:
 *   - The function is designed to be called for each unvisited node in the graph.
 *   - The resulting topological order will be stored in the stack 's', with the top of the stack being the last node in the order.
 *   - Kahn's Algorithm is efficient and runs in O(V + E) time, where V is the number of vertices and E is the number of edges.
 */

void calculate_indegree(map<int, vector<int>> graph, map<int, int> &indegrees)
{
  for (const auto &element : graph)
    indegrees[element.first] = 0;

  for (const auto &element : graph)
  {
    // element.second are neighbors vector
    for (const int &item : element.second)
      indegrees[item]++;
  }
}

void topological_sort_kahns(map<int, vector<int>> graph)
{
  map<int, int> indegrees;
  calculate_indegree(graph, indegrees);

  queue<int> q;
  for (const auto &element : indegrees)
  {
    if (indegrees[element.first] == 0)
      q.push(element.first);
  }

  while (!q.empty())
  {
    int current = q.front();
    q.pop();
    cout << current << ' ';

    // dependency of current element to its neighbors is gone now, so their indegree reduces by 1
    for (const int &neighbor : graph[current])
    {
      indegrees[neighbor]--;
      if (indegrees[neighbor] == 0)
        q.push(neighbor);
    }
  }

  cout << endl;
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

  topological_sort_kahns(graph_map);
}
