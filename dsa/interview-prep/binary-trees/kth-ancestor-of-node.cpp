// https://www.naukri.com/code360/problems/kth-ancestor-of-a-node-in-binary-tree_842561

#include <iostream>
#include <vector>
#include "node.hpp"
using namespace std;

int kth_ancestor_of_node(Node *root, Node *n, int k, int *ans)
{
  if (root == NULL)
    return -1;

  if (root == n)
    return 0;

  int left = kth_ancestor_of_node(root->left, n, k, ans);
  int right = kth_ancestor_of_node(root->right, n, k, ans);

  if (left + 1 == k || right + 1 == k)
    *ans = root->data;

  if (left == -1 && right == -1)
    return -1;

  return left == -1 ? right + 1 : left + 1;
}

int main()
{
  vector<int> preorder = {1, 2, 4, -1, -1, 5, -1, -1, 3, -1, 6, -1, -1};
  Node *tree = build_tree(preorder);

  Node *five = tree->left->right;

  int *ans;
  kth_ancestor_of_node(tree, five, 2, ans);
  cout << *ans << endl; // 1

  return 0;
}
