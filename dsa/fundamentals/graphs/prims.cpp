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

void prims(const vector<vector<int>> &cost)
{
  vector<int> current_costs(cost.size(), I);
  vector<bool> mst(cost.size(), false);
  vector<int> parents(cost.size(), -1);

  int i = 1;

  current_costs[i] = 0;
  parents[i] = -1; // it is already -1, just for clarification
  mst[i] = true;

  while (true)
  {
    int min_cost = I;
    int u = -1;

    for (int j = 1; j < cost.size(); j++)
    {
      if (cost[i][j] != I && !mst[j] && cost[i][j] < min_cost)
      {
        min_cost = cost[i][j];
        u = j;
      }
    }

    if (u != -1)
    {
      mst[u] = true;
      current_costs[u] = cost[i][u];
      parents[u] = i;

      i = u;
    }
    else
    {
      // ith element has no adjacent edges
      break;
    }
  }

  int total_cost = 0;
  for (int i = 2; i < cost.size(); i++)
  {
    total_cost += current_costs[i];
    cout << parents[i] << " -- " << i << " : " << current_costs[i] << endl;
  }
  cout << "Total: " << total_cost << endl;
}

int main()
{
  const int n = 8;

  vector<vector<int>> graph_matrix(n, vector<int>(n, I));

  populate_graph(graph_matrix);
  prims(graph_matrix);

  return 0;
}
