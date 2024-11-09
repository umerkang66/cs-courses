// https://leetcode.com/problems/validate-binary-search-tree/

#include <iostream>
#include "node.hpp"
using namespace std;

bool validate_bst(Node *root, Node *min = NULL, Node *max = NULL)
{
  if (root == NULL)
    return true;

  if ((min && root->data <= min->data) ||
      (max && root->data >= max->data))
    return false;

  // dry run it
  return validate_bst(root->left, min, root) &&
         validate_bst(root->right, root, max);
}

int main()
{
  vector<int> arr = {8, 5, 3, 6, 1, 4, 10, 11, 14};
  Node *tree = build_from_arr(arr);

  cout << validate_bst(tree) << endl; // true

  return 0;
}
