#include <iostream>
#include "node.hpp"
using namespace std;

Node *search(Node *root, int n)
{
  if (root == NULL)
    return NULL;

  if (n < root->data)
    return search(root->left, n);
  else if (n > root->data)
    return search(root->right, n);
  else
    return root;
}

int main()
{
  vector<int> arr = {8, 5, 3, 6, 1, 4, 10, 11, 14};
  Node *tree = build_from_arr(arr);
  cout << search(tree, 6) << endl; // some pointer
  cout << search(tree, 7) << endl; // NULL

  return 0;
}
