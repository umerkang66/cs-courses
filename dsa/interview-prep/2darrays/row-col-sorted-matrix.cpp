#include <iostream>
using namespace std;

void search(int **matrix, int rows, int cols, int target)
{
  // start looking from the top right
  int i = 0;
  int j = cols - 1;

  while (i < rows && j >= 0)
  {
    // from this top right element, left elements are smaller and down elements are larger

    // moves downwards
    if (target > matrix[i][j])
      i++;
    // moves left
    else if (target < matrix[i][j])
      j--;
    else
    {
      cout << i << " " << j << endl;
      return;
    }
  }

  cout << -1 << " " << -1 << endl;
}

int main()
{
  int m = 4;
  int n = 4;

  // Dynamically allocate a 2D array
  int **matrix = new int *[m];
  for (int i = 0; i < m; i++)
    matrix[i] = new int[n];

  // Initialize matrix
  int data[m][n] = {
      {10, 20, 30, 40},
      {15, 25, 35, 45},
      {27, 29, 37, 48},
      {32, 33, 39, 50},
  };

  for (int i = 0; i < m; i++)
  {
    for (int j = 0; j < n; j++)
      matrix[i][j] = data[i][j];
  }

  search(matrix, m, n, 34);

  // Deallocate memory
  for (int i = 0; i < m; i++)
    delete[] matrix[i];
  delete[] matrix;

  return 0;
}
