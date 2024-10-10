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

vector<vector<int>> generate_board(int m, int n)
{
  vector<vector<int>> board(m, vector<int>(n, 0));
  return board;
}

void grid_ways(vector<vector<int>> board, int row = 0, int col = 0)
{
  if (row == board.size() - 1 && col == board[0].size() - 1)
  {
    board[row][col] = 1;
    print_board(board);
    return;
  }

  if (row == board.size() || col == board[0].size())
    return;

  board[row][col] = 1;
  grid_ways(board, row, col + 1);
  grid_ways(board, row + 1, col);
  // while backtracking, reset
  board[row][col] = 0;
}

int grid_ways_count(vector<vector<int>> board, int row = 0, int col = 0)
{
  if (
      (row == board.size() - 2 && col == board[0].size() - 1) ||
      (row == board.size() - 1 && col == board[0].size() - 2))
  {
    return 1;
  }

  if (row == board.size() || col == board[0].size())
    return 0;

  return grid_ways_count(board, row, col + 1) + grid_ways_count(board, row + 1, col);
}

int main()
{
  vector<vector<int>> board = generate_board(4, 5);
  cout << grid_ways_count(board) << endl;
  grid_ways(board);

  return 0;
}
