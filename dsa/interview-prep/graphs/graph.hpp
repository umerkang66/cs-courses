#include <iostream>
#include <map>
#include <vector>
#include <queue>

using namespace std;

// THESE ARE UNDIRECTED GRAPHS
template <typename T>
class GraphAdjacencyList
{
  map<T, vector<T> *> adjacency_lists;

public:
  void add_vertex(T vertex)
  {
    adjacency_lists[vertex] = new vector<T>();
  }

  void add_edge(T vertex1, T vertex2)
  {
    // check if vertex1 and vertex2 exist, if not, add them
    if (adjacency_lists.find(vertex1) == adjacency_lists.end())
      add_vertex(vertex1);
    if (adjacency_lists.find(vertex2) == adjacency_lists.end())
      add_vertex(vertex2);

    // add the edge in both directions
    adjacency_lists[vertex1]->push_back(vertex2);
    adjacency_lists[vertex2]->push_back(vertex1);
  }

  void visualize()
  {
    for (const auto &pair : adjacency_lists)
    {
      cout << pair.first << ": ";
      for (const T &neighbor : *pair.second)
        cout << neighbor << " ";
      cout << endl;
    }
  }

  void bfs(T start)
  {
    queue<T> q;
    map<T, bool> visited;

    q.push(start);

    while (!q.empty())
    {
      T current = q.front();
      q.pop();

      if (visited[current])
        continue;

      visited[current] = true;
      cout << current << " ";

      for (T &neighbor : *adjacency_lists[current])
      {
        if (!visited[neighbor])
          q.push(neighbor);
      }
    }
  }

  void dfs_helper(T vertex, map<T, bool> &visited)
  {
    if ((*adjacency_lists[vertex]).empty())
      return;

    visited[vertex] = true;
    cout << vertex << " ";

    for (const T &neighbor : *adjacency_lists[vertex])
    {
      if (!visited[neighbor])
        dfs_helper(neighbor, visited);
    }
  }

  void dfs(T start)
  {
    map<T, bool> m;
    dfs_helper(start, m);
  }

  ~GraphAdjacencyList()
  {
    for (auto &pair : adjacency_lists)
      delete pair.second;
  }
};

template <typename T>
class WeightedGraphAdjacencyList
{
  map<T, vector<pair<T, int>> *> list;

public:
  void add_vertex(T vertex)
  {
    list[vertex] = new vector<pair<T, int>>();
  }

  void add_edge(T vertex1, T vertex2, int weight)
  {
    // check if vertex1 and vertex2 exist, if not, add them
    if (list.find(vertex1) == list.end())
      add_vertex(vertex1);
    if (list.find(vertex2) == list.end())
      add_vertex(vertex2);

    // add the edge in both directions
    list[vertex1]->push_back(make_pair(vertex2, weight));
    list[vertex2]->push_back(make_pair(vertex1, weight));
  }

  void visualize()
  {
    for (const auto &pair : list)
    {
      cout << pair.first << " -> ";
      for (const auto &neighbor : *pair.second)
        cout << "(" << neighbor.first << ", " << neighbor.second << ") ";
      cout << endl;
    }
  }

  ~WeightedGraphAdjacencyList()
  {
    for (auto &pair : list)
      delete pair.second;
  }
};
