// https://leetcode.com/problems/range-sum-of-bst/

#include <iostream>
#include "node.hpp"
using namespace std;

void print_in_range(Node *root, int start, int end)
{
  if (root == NULL)
    return;

  if (root->data < start)
    print_in_range(root->right, start, end);
  else if (root->data > end)
    print_in_range(root->left, start, end);
  else
  {
    cout << root->data << ' ';
    print_in_range(root->left, start, end);
    print_in_range(root->right, start, end);
  }
}

int main()
{
  vector<int> arr = {8, 5, 3, 6, 1, 4, 10, 11, 14};
  Node *tree = build_from_arr(arr);

  print_in_range(tree, 5, 12);
  cout << endl;

  return 0;
}
