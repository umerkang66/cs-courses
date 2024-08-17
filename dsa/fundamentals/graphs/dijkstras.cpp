#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int I = INT16_MAX;

void populate_graph(vector<vector<int>> &adj_matrix)
{
  adj_matrix[1][2] = 6;
  adj_matrix[1][3] = 5;
  adj_matrix[1][4] = 5;

  adj_matrix[2][5] = 1;

  adj_matrix[3][2] = 2;
  adj_matrix[3][5] = 1;

  adj_matrix[4][3] = 2;
  adj_matrix[4][6] = 3;

  adj_matrix[5][7] = 3;

  adj_matrix[6][7] = 2;
}

vector<int> dijkstras(const vector<vector<int>> &graph, int source = 1)
{
  vector<bool> visited(graph.size(), false);
  vector<int> result(graph.size(), I);

  // Priority queue to store (distance, node) pairs
  // first template is the form of data
  // second template is the container of that form
  // third is instead of creating max-heap create min-heap
  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> index_queue;

  visited[source] = true;
  result[source] = 0;

  // Push the source node into the priority queue
  index_queue.push({0, source});

  while (!index_queue.empty())
  {
    int current_source = index_queue.top().second;
    index_queue.pop();

    // Traverse all adjacent nodes
    for (int j = 1; j < graph[0].size(); j++)
    {
      if (j != current_source && graph[current_source][j] != I && !visited[j])
      {
        // If a shorter path is found
        if (result[current_source] + graph[current_source][j] < result[j])
        {
          result[j] = result[current_source] + graph[current_source][j];
          // Push the adjacent node with its updated distance into the priority queue
          index_queue.push({result[j], j});
          visited[j] = true;
        }
      }
    }
  }

  return result;
}

int main()
{
  const int n = 7 + 1;

  vector<vector<int>> graph_matrix(n, vector<int>(n, I));

  populate_graph(graph_matrix);
  vector<int> result = dijkstras(graph_matrix);

  cout << "Paths from 1: " << endl;
  for (int i = 1; i < result.size(); i++)
  {
    string to_print = result[i] == I ? "I" : to_string(result[i]);
    cout << i << ": " << to_print << endl;
  }

  return 0;
}
