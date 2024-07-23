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

int find_parent(vector<int> &set, int n)
{
  int x = n;
  while (set[x] > 0)
    x = set[x];
  return x;
}

void kruskals(const vector<vector<int>> &cost)
{
  int total_edges = 0;
  for (int i = 0; i < cost.size(); i++)
  {
    for (int j = i; j < cost.size(); j++)
    {
      if (cost[i][j] != I)
        total_edges++;
    }
  }

  vector<vector<int>> edges(3, vector<int>(total_edges));
  int edge_counter = 0;

  for (int i = 0; i < cost.size(); i++)
  {
    for (int j = i; j < cost.size(); j++)
    {
      if (cost[i][j] != I)
      {
        edges[0][edge_counter] = i;
        edges[1][edge_counter] = j;
        edges[2][edge_counter] = cost[i][j];

        edge_counter++;
      }
    }
  }

  vector<int> set(cost.size(), -1);
  vector<int> included(total_edges, 0);
  vector<vector<int>> ans(3, vector<int>(cost.size()));
  int ans_counter = 0;

  while (true)
  {
    int min_cost = I;
    int u = -1;
    for (int i = 0; i < edges[0].size(); i++)
    {
      if (included[i] != 1 && edges[2][i] < min_cost)
      {
        min_cost = edges[2][i];
        u = i;
      }
    }

    if (u != -1)
    {
      // mark the included at u
      included[u] = 1;

      int first_p = find_parent(set, edges[0][u]);
      int second_p = find_parent(set, edges[1][u]);

      // check if they don't have the same parent
      if (first_p != second_p)
      {
        // they don't have same parent
        ans[0][ans_counter] = edges[0][u];
        ans[1][ans_counter] = edges[1][u];
        ans[2][ans_counter] = edges[2][u];

        ans_counter++;

        // update the set
        if (set[first_p] < set[second_p])
        {
          set[first_p] += set[second_p];
          set[second_p] = first_p;
        }
        else
        {
          set[second_p] += set[first_p];
          set[first_p] = second_p;
        }
      }
    }
    else
    {
      break;
    }
  }

  cout << "Set: ";
  for (int i = 0; i < set.size(); i++)
  {
    cout << set[i] << ' ';
  }
  cout << endl;

  int total_cost = 0;
  for (int i = 0; i < ans[0].size(); i++)
  {
    total_cost += ans[2][i];
    cout << ans[0][i] << " -- " << ans[1][i] << " : " << ans[2][i] << endl;
  }
  cout << "Total: " << total_cost << endl;
}

int main()
{
  const int n = 8;

  vector<vector<int>> graph_matrix(n, vector<int>(n, I));

  populate_graph(graph_matrix);
  kruskals(graph_matrix);

  return 0;
}
