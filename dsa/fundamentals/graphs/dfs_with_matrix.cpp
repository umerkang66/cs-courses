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

void dfs(const vector<vector<int>> &adj_matrix, vector<int> &visited, int current_node = 1)
{
  if (visited[current_node] == 1)
    return;

  cout << current_node << ' ';
  visited[current_node] = 1;

  for (int i = 1; i < adj_matrix[current_node].size(); i++)
  {
    if (adj_matrix[current_node][i] == 1 && visited[i] == 0)
      dfs(adj_matrix, visited, i);
  }
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

  vector<int> visited(graph_matrix.size(), 0);
  dfs(graph_matrix, visited);
  cout << endl;

  return 0;
}
