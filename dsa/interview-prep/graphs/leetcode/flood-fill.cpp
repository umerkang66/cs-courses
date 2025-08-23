// https://leetcode.com/problems/flood-fill/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
  void helper(vector<vector<int>> &image, int row, int col, int new_color, vector<vector<bool>> &visited, int old_color)
  {
    int n = image.size();
    int m = image[0].size();

    if (row >= n || col >= m || row < 0 || col < 0)
      return;

    image[row][col] = new_color;
    visited[row][col] = true;

    if (col + 1 < m && !visited[row][col + 1] && image[row][col + 1] == old_color)
      helper(image, row, col + 1, new_color, visited, old_color);

    if (col - 1 >= 0 && !visited[row][col - 1] && image[row][col - 1] == old_color)
      helper(image, row, col - 1, new_color, visited, old_color);

    if (row + 1 < n && !visited[row + 1][col] && image[row + 1][col] == old_color)
      helper(image, row + 1, col, new_color, visited, old_color);

    if (row - 1 >= 0 && !visited[row - 1][col] && image[row - 1][col] == old_color)
      helper(image, row - 1, col, new_color, visited, old_color);
  }

  vector<vector<int>> floodFill(vector<vector<int>> &image, int sr, int sc, int color)
  {
    vector<vector<bool>> visited(image.size(), vector<bool>(image[0].size(), false));

    helper(image, sr, sc, color, visited, image[sr][sc]);

    return image;
  }
};
