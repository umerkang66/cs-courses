#include <iostream>
#include <map>
#include <vector>
#include <queue>

using namespace std;

// UNDIRECTED GRAPH
template <typename T>
class GraphAdjacencyList
{
  map<T, vector<T> *> adjacency_lists;

public:
  map<T, vector<T> *> get_graph() { return adjacency_lists; }

  void add_vertex(T vertex)
  {
    adjacency_lists[vertex] = new vector<T>();
  }

  void add_edge(T vertex1, T vertex2)
  {
    if (adjacency_lists.find(vertex1) == adjacency_lists.end())
      add_vertex(vertex1);
    if (adjacency_lists.find(vertex2) == adjacency_lists.end())
      add_vertex(vertex2);

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

  void bfs_helper(T start, map<T, bool> &visited)
  {
    queue<T> q;
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

  void bfs(T start)
  {
    map<T, bool> visited;
    for (const auto &pair : adjacency_lists)
      visited[pair.first] = false;

    bfs_helper(start, visited);

    for (const auto &pair : adjacency_lists)
    {
      if (!visited[pair.first])
      {
        cout << "\nDisconnected component: ";
        bfs_helper(pair.first, visited);
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
    map<T, bool> visited;
    for (const auto &pair : adjacency_lists)
      visited[pair.first] = false;

    dfs_helper(start, visited);

    for (const auto &pair : adjacency_lists)
    {
      if (!visited[pair.first])
      {
        cout << "\nDisconnected component: ";
        dfs_helper(pair.first, visited);
      }
    }
  }

  ~GraphAdjacencyList()
  {
    for (auto &pair : adjacency_lists)
      delete pair.second;
  }
};

// WEIGHTED UNDIRECTED GRAPH
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
    if (list.find(vertex1) == list.end())
      add_vertex(vertex1);
    if (list.find(vertex2) == list.end())
      add_vertex(vertex2);

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

// DIRECTED GRAPH
template <typename T>
class DirectedGraphAdjacencyList
{
  map<T, vector<T>> adjacency_lists;

public:
  map<T, vector<T>> get_graph() { return adjacency_lists; }

  void add_vertex(T vertex)
  {
    if (adjacency_lists.find(vertex) == adjacency_lists.end())
      adjacency_lists[vertex] = vector<T>();
  }

  void add_edge(T from, T to)
  {
    if (adjacency_lists.find(from) == adjacency_lists.end())
      add_vertex(from);
    if (adjacency_lists.find(to) == adjacency_lists.end())
      add_vertex(to);

    adjacency_lists[from].push_back(to);
  }

  void visualize()
  {
    for (const auto &pair : adjacency_lists)
    {
      cout << pair.first << " -> ";
      for (const T &neighbor : pair.second)
        cout << neighbor << " ";
      cout << endl;
    }
  }

  void bfs_helper(T start, map<T, bool> &visited)
  {
    queue<T> q;
    q.push(start);

    while (!q.empty())
    {
      T current = q.front();
      q.pop();

      if (visited[current])
        continue;
      visited[current] = true;

      cout << current << " ";

      for (T &neighbor : adjacency_lists[current])
      {
        if (!visited[neighbor])
          q.push(neighbor);
      }
    }
  }

  void bfs(T start)
  {
    map<T, bool> visited;
    for (const auto &pair : adjacency_lists)
      visited[pair.first] = false;

    bfs_helper(start, visited);

    for (const auto &pair : adjacency_lists)
    {
      if (!visited[pair.first])
      {
        cout << "\nDisconnected component: ";
        bfs_helper(pair.first, visited);
      }
    }
  }

  void dfs_helper(T vertex, map<T, bool> &visited)
  {
    visited[vertex] = true;
    cout << vertex << " ";

    for (const T &neighbor : adjacency_lists[vertex])
    {
      if (!visited[neighbor])
        dfs_helper(neighbor, visited);
    }
  }

  void dfs(T start)
  {
    map<T, bool> visited;
    for (const auto &pair : adjacency_lists)
      visited[pair.first] = false;

    dfs_helper(start, visited);

    for (const auto &pair : adjacency_lists)
    {
      if (!visited[pair.first])
      {
        cout << "\nDisconnected component: ";
        dfs_helper(pair.first, visited);
      }
    }
  }
};

// WEIGHTED DIRECTED GRAPH
template <typename T>
class WeightedDirectedGraphAdjacencyList
{
  map<T, vector<pair<T, int>> *> list;

public:
  map<T, vector<pair<T, int>> *> &get_graph()
  {
    return list;
  }

  void add_vertex(T vertex)
  {
    if (list.find(vertex) == list.end())
      list[vertex] = new vector<pair<T, int>>();
  }

  void add_edge(T from, T to, int weight)
  {
    if (list.find(from) == list.end())
      add_vertex(from);
    if (list.find(to) == list.end())
      add_vertex(to);

    list[from]->push_back(make_pair(to, weight));
  }

  void visualize()
  {
    for (const auto &p : list)
    {
      cout << p.first << " -> ";
      for (const auto &neighbor : *p.second)
        cout << "(" << neighbor.first << ", " << neighbor.second << ") ";
      cout << endl;
    }
  }

  ~WeightedDirectedGraphAdjacencyList()
  {
    for (auto &p : list)
      delete p.second;
  }
};
