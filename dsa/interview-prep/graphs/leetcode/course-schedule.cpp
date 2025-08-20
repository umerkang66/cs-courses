// https://leetcode.com/problems/course-schedule/

#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
  bool is_cycle(vector<vector<int>> &edges, int src, vector<int> &visited, vector<int> &recursion_path)
  {
    visited[src] = true;
    recursion_path[src] = true;

    for (int i = 0; i < edges.size(); i++)
    {
      int u = edges[i][1];
      int v = edges[i][0];
      if (u == src)
      {
        if (!visited[v])
        {
          if (is_cycle(edges, v, visited, recursion_path))
            return true;
        }
        else
        {
          if (recursion_path[v])
            return true;
        }
      }
    }

    recursion_path[src] = false;
    return false;
  }

  bool canFinish(int numCourses, vector<vector<int>> &prerequisites)
  {
    int V = numCourses;
    vector<int> visited(V, false);
    vector<int> recursion_path(V, false);

    for (int i = 0; i < V; i++)
    {
      if (!visited[i])
      {
        if (is_cycle(prerequisites, i, visited, recursion_path))
          return false;
      }
    }

    return true;
  }
};
