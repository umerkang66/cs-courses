#include <iostream>
#include <queue>
#include <vector>

using namespace std;

void populate_graph(vector<vector<int>> &adj_matrix)
{
  adj_matrix[1][2] = 1;
  adj_matrix[1][3] = 1;
  adj_matrix[1][4] = 1;

  adj_matrix[2][1] = 1;
  adj_matrix[2][3] = 1;

  adj_matrix[3][1] = 1;
  adj_matrix[3][2] = 1;
  adj_matrix[3][4] = 1;
  adj_matrix[3][5] = 1;

  adj_matrix[4][1] = 1;
  adj_matrix[4][3] = 1;
  adj_matrix[4][5] = 1;

  adj_matrix[5][3] = 1;
  adj_matrix[5][4] = 1;
  adj_matrix[5][6] = 1;
  adj_matrix[5][7] = 1;

  adj_matrix[6][5] = 1;
  adj_matrix[7][5] = 1;
}

void bfs(const vector<vector<int>> &adj_matrix, int start = 1)
{
  // for which imaginary node is visited
  vector<int> visited(adj_matrix.size(), 0);
  queue<int> tracking_queue;

  tracking_queue.push(start);

  while (!tracking_queue.empty())
  {
    int current_vertex = tracking_queue.front();
    visited[current_vertex] = 1;
    tracking_queue.pop();

    cout << current_vertex << ' ';

    for (int i = 0; i < adj_matrix[current_vertex].size(); i++)
    {
      int connected_vertex = adj_matrix[current_vertex][i];

      if (connected_vertex == 1 && visited[i] == 0)
      {
        tracking_queue.push(i);
        visited[i] = 1;
      }
    }
  }

  cout << endl;
}

int main()
{
  int n = 8;

  vector<vector<int>> graph_matrix(n);
  for (vector<int> &row : graph_matrix)
    row = vector<int>(n);

  for (vector<int> &row : graph_matrix)
  {
    for (int &column : row)
      column = 0;
  }

  populate_graph(graph_matrix);

  for (const vector<int> &row : graph_matrix)
  {
    for (const int &column : row)
      cout << column << ' ';
    cout << endl;
  }

  cout << endl;

  bfs(graph_matrix);

  return 0;
}
