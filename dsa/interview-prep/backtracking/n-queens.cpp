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

  cout << endl;
}

bool is_valid(vector<vector<int>> board, int row, int col)
{
  // check for row
  for (int j = 0; j < board.size(); j++)
  {
    if (board[row][j] == 1)
      return false;
  }

  //  check for straight column
  int i = row;
  while (i >= 0)
  {
    if (board[i][col] == 1)
      return false;
    i--;
  }

  // check for left diagonal
  i = row;
  int j = col;
  while (i >= 0 && j >= 0)
  {
    if (board[i][j] == 1)
      return false;
    i--;
    j--;
  }

  // check for right diagonal
  i = row;
  j = col;
  while (i >= 0 && j < board[0].size())
  {
    if (board[i][j] == 1)
      return false;
    i--;
    j++;
  }

  return true;
}

// put the queens on the safe position
void nqueens(vector<vector<int>> board, int curr_row = 0)
{
  if (curr_row >= board.size())
  {
    print_board(board);
    return;
  }

  // for every column, try and place the queen
  for (int j = 0; j < board[0].size(); j++)
  {
    if (is_valid(board, curr_row, j))
    {
      board[curr_row][j] = 1;
      nqueens(board, curr_row + 1);
      // while backtracking - reset the condition
      board[curr_row][j] = 0;
    }
  }
}

int main()
{
  vector<vector<int>> board = {
      {0, 0, 0, 0},
      {0, 0, 0, 0},
      {0, 0, 0, 0},
      {0, 0, 0, 0},
  };

  print_board(board);
  nqueens(board);

  return 0;
}
