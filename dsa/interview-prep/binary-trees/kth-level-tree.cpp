#include <iostream>
#include <vector>
#include "node.hpp"
using namespace std;

void kth_level_tree(Node *root, int k, int level = 1)
{
  if (root == NULL)
    return;

  if (level == k)
    cout << root->data << ' ';

  kth_level_tree(root->left, k, level + 1);
  kth_level_tree(root->right, k, level + 1);
}

int main()
{
  vector<int> preorder = {1, 2, 4, -1, -1, 5, -1, -1, 3, -1, 6, -1, -1};
  Node *tree = build_tree(preorder);

  kth_level_tree(tree, 3);
  cout << endl;

  return 0;
}
