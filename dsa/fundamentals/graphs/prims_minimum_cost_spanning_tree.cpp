#include <iostream>
#include <vector>

using namespace std;

const int I = INT16_MAX;

void populate_graph(vector<vector<int>> &adj_matrix)
{
  adj_matrix[1][2] = 25;
  adj_matrix[1][6] = 5;

  adj_matrix[2][1] = 25;
  adj_matrix[2][3] = 12;
  adj_matrix[2][7] = 10;

  adj_matrix[3][2] = 12;
  adj_matrix[3][4] = 8;

  adj_matrix[4][3] = 8;
  adj_matrix[4][5] = 16;
  adj_matrix[4][7] = 14;

  adj_matrix[5][4] = 16;
  adj_matrix[5][6] = 20;
  adj_matrix[5][7] = 18;

  adj_matrix[6][1] = 5;
  adj_matrix[6][5] = 20;

  adj_matrix[7][2] = 10;
  adj_matrix[7][4] = 14;
  adj_matrix[7][5] = 18;
}

void prims_algorithm(const vector<vector<int>> &graph)
{
  vector<int> near(graph.size(), I);
  vector<vector<int>> spanning_tree(2, vector<int>(graph.size() - 2));

  int min_cost = I;
  int from = -1;
  int to = -1;

  for (int i = 1; i < graph.size(); i++)
  {
    for (int j = i; j < graph[0].size(); j++)
    {
      if (graph[i][j] < min_cost) // cost < min
      {
        min_cost = graph[i][j];
        from = i;
        to = j;
      }
    }
  }

  spanning_tree[0][0] = from;
  spanning_tree[1][0] = to;
  // these are already included
  near[from] = 0;
  near[to] = 0;

  for (int i = 1; i < graph.size(); i++)
  {
    if (near[i] != 0)
    {
      // check if the ith is nearer to 'from' or nearer to 'to'
      if (graph[i][from] < graph[i][to])
        near[i] = from;
      else
        near[i] = to;
    }
  }

  for (int i = 1; i < graph.size() - 2; i++)
  {
    int min_cost = I;
    int k = -1;

    for (int j = 1; j < graph.size(); j++)
    {
      if (near[j] != 0 && graph[j][near[j]] < min_cost)
      {
        min_cost = graph[j][near[j]];
        k = j;
      }
    }

    spanning_tree[0][i] = k;
    spanning_tree[1][i] = near[k];
    near[k] = 0;

    for (int j = 1; j < graph.size(); j++)
    {
      if (near[j] != 0 && graph[j][k] < graph[j][near[j]])
        near[j] = k;
    }
  }

  // printing
  for (int j = 0; j < spanning_tree[0].size(); j++)
  {
    cout << spanning_tree[0][j] << " -- " << spanning_tree[1][j] << " : " << graph[spanning_tree[0][j]][spanning_tree[1][j]] << endl;
  }
}

int main()
{
  const int n = 8;

  vector<vector<int>> graph_matrix(n, vector<int>(n, I));

  populate_graph(graph_matrix);

  prims_algorithm(graph_matrix);

  return 0;
}
