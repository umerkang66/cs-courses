// https://leetcode.com/problems/course-schedule-ii/

#include <iostream>
#include <vector>
#include <map>
#include <stack>

using namespace std;

class Solution
{
public:
  bool topological_sort(vector<vector<int>> &edges, int src, map<int, bool> &visited, stack<int> &sorted_order, map<int, bool> &recursion_path)
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
          if (!topological_sort(edges, v, visited, sorted_order, recursion_path))
            return false;
        }
        else
        {
          // there is a cycle
          if (recursion_path[v])
            return false;
        }
      }
    }

    recursion_path[src] = false;
    sorted_order.push(src);
    return true;
  }

  vector<int> findOrder(int numCourses, vector<vector<int>> &prerequisites)
  {
    stack<int> sorted_order;
    map<int, bool> visited;
    map<int, bool> recursion_path;

    for (int i = 0; i < numCourses; i++)
    {
      if (!visited[i])
        if (!topological_sort(prerequisites, i, visited, sorted_order, recursion_path))
        {
          return {};
        }
    }

    vector<int> result;
    while (!sorted_order.empty())
    {
      result.push_back(sorted_order.top());
      sorted_order.pop();
    }
    return result;
  }
};
