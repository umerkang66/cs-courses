#include <iostream>
#include <vector>
using namespace std;

void print_board(vector<vector<int>> board)
{
  for (int i = 0; i < board.size(); i++)
  {
    for (int j = 0; j < board[0].size(); j++)
      cout << board[i][j] << ' ';
    cout << endl;
  }
}

bool is_valid(vector<vector<int>> board, int row, int col, int num)
{
  // check down the column
  for (int i = 0; i < board.size(); i++)
  {
    if (board[i][col] == num)
      return false;
  }

  // check left to right in the row
  for (int j = 0; j < board[0].size(); j++)
  {
    if (board[row][j] == num)
      return false;
  }

  // check in the 3x3 matrix
  int start_row = row / 3 * 3;
  int start_col = col / 3 * 3;

  for (int i = start_row; i < start_row + 3; i++)
  {
    for (int j = start_col; j < start_col + 3; j++)
    {
      if (board[i][j] == num)
        return false;
    }
  }

  return true;
}

void sudoku_solver(vector<vector<int>> board, int row = 0, int col = 0)
{
  if (row == board.size())
    return print_board(board);

  if (col == board[0].size())
    return sudoku_solver(board, row + 1, 0);

  // if the cell is empty
  if (board[row][col] == 0)
  {
    for (int num = 1; num <= 9; num++)
    {
      if (is_valid(board, row, col, num))
      {
        board[row][col] = num;
        sudoku_solver(board, row, col + 1);
        board[row][col] = 0;
      }
    }
  }
  else
    sudoku_solver(board, row, col + 1);
}

int main(int argc, const char *argv[])
{
  vector<vector<int>> board = {
      {5, 3, 0, 0, 7, 0, 0, 0, 0},
      {6, 0, 0, 1, 9, 5, 0, 0, 0},
      {0, 9, 8, 0, 0, 0, 0, 6, 0},
      {8, 0, 0, 0, 6, 0, 0, 0, 3},
      {4, 0, 0, 8, 0, 3, 0, 0, 1},
      {7, 0, 0, 0, 2, 0, 0, 0, 6},
      {0, 6, 0, 0, 0, 0, 2, 8, 0},
      {0, 0, 0, 4, 1, 9, 0, 0, 5},
      {0, 0, 0, 0, 8, 0, 0, 7, 9}};

  sudoku_solver(board);

  return 0;
}
