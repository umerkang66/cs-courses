// Abdul Bari Bellman Ford: https://www.youtube.com/watch?v=FtN3BYH2Zes

#include <iostream>
#include <vector>

using namespace std;

const int I = INT16_MAX;

void populate_graph(vector<vector<int>> &adj_matrix)
{
  adj_matrix[1][2] = 6;
  adj_matrix[1][3] = 5;
  adj_matrix[1][4] = 5;

  adj_matrix[2][5] = -1;

  adj_matrix[3][2] = -2;
  adj_matrix[3][5] = 1;

  adj_matrix[4][3] = -2;
  adj_matrix[4][6] = -1;

  adj_matrix[5][7] = 3;

  adj_matrix[6][7] = 2;
}

vector<int> bellman_ford(const vector<vector<int>> &graph, int source = 1)
{
  // POPULATE EDGES
  vector<vector<int>> edges;
  for (int i = 1; i < graph.size(); i++)
  {
    for (int j = 1; j < graph.size(); j++)
    {
      if (graph[i][j] < I)
      {
        vector<int> edge(2);
        // there is a edge
        edge[0] = i;
        edge[1] = j;
        edges.push_back(edge);
      }
    }
  }

  vector<int> result(graph.size(), I);
  result[source] = 0;

  bool is_changed = true;
  int i = 1;

  // for Worst Case, this should only run n-1 times, if there even relaxation after n-1 time, there is a negative weight cycle
  while (is_changed && i < graph.size() - 1)
  {
    // the second condition is for negative weighted cycles
    is_changed = false;
    for (const vector<int> &edge : edges)
    {
      // If a shorter path is found
      if (result[edge[0]] + graph[edge[0]][edge[1]] < result[edge[1]])
      {
        result[edge[1]] = result[edge[0]] + graph[edge[0]][edge[1]];
        is_changed = true;
      }
    }
    i++;
  }

  return result;
}

int main()
{
  const int n = 7 + 1;

  vector<vector<int>> graph_matrix(n, vector<int>(n, I));

  populate_graph(graph_matrix);
  vector<int> result = bellman_ford(graph_matrix);

  cout << "Paths from 1: " << endl;
  for (int i = 1; i < result.size(); i++)
  {
    string to_print = result[i] == I ? "I" : to_string(result[i]);
    cout << i << ": " << to_print << endl;
  }

  return 0;
}
