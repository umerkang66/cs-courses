#include <iostream>
using namespace std;

void spiral(int **matrix, int rows, int cols)
{
  int start_row = 0;
  int start_col = 0;
  int end_row = rows - 1;
  int end_col = cols - 1;

  while (start_row < end_row && start_col < end_col)
  {
    // top
    for (int j = start_col; j <= end_col; j++)
      cout << matrix[start_row][j] << " ";

    // right
    for (int i = start_row + 1; i <= end_row; i++)
      cout << matrix[i][end_col] << " ";

    // bottom
    for (int j = end_col - 1; j >= start_col; j--)
    {
      // this should be already printed in the top  traversal
      if (start_row == end_row)
        break;
      cout << matrix[end_row][j] << " ";
    }

    // left
    for (int i = end_row - 1; i > start_row; i--)
    {
      // this should be already printed in the right traversal
      if (start_col == end_col)
        break;
      cout << matrix[i][start_col] << " ";
    }

    start_row++;
    start_col++;
    end_row--;
    end_col--;
  }
  cout << endl;
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
      {1, 2, 3, 4},
      {5, 6, 7, 8},
      {9, 10, 11, 12},
      {13, 14, 15, 16},
  };

  for (int i = 0; i < m; i++)
  {
    for (int j = 0; j < n; j++)
      matrix[i][j] = data[i][j];
  }

  spiral(matrix, m, n);

  // Deallocate memory
  for (int i = 0; i < m; i++)
    delete[] matrix[i];
  delete[] matrix;

  return 0;
}
