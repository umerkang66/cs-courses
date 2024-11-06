// https://www.naukri.com/code360/problems/convert-a-binary-tree-to-its-sum-tree_920395

#include <iostream>
#include <vector>
#include "./node.hpp"
using namespace std;

int transform_to_sum_tree(Node *root)
{
  if (root == NULL)
    return 0;

  int left = transform_to_sum_tree(root->left);
  int right = transform_to_sum_tree(root->right);

  int answer = left + right + root->data;

  root->data = left + right;

  return answer;
}

int main()
{
  vector<int> preorder = {1, 2, 4, -1, -1, 5, -1, -1, 3, -1, 6, -1, -1};
  Node *tree = build_tree(preorder);

  show(tree);
  transform_to_sum_tree(tree);
  show(tree);

  return 0;
}
