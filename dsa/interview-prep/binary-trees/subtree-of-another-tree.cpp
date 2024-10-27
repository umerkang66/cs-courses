// https://leetcode.com/problems/subtree-of-another-tree/

#include <iostream>
#include <vector>
#include "./node.hpp"
using namespace std;

bool is_identical(Node *root1, Node *root2)
{
  if (root1 == NULL && root2 == NULL)
    return true;
  else if (root1 == NULL || root2 == NULL)
    return false;

  if (root1->data != root2->data)
    return false;

  bool left_ans = is_identical(root1->left, root2->left);
  bool right_ans = is_identical(root1->right, root2->right);

  return left_ans && right_ans;
}

bool is_subtree(Node *node, Node *sub_tree_node)
{
  if (node == NULL && sub_tree_node == NULL)
    return true;
  else if (node == NULL || sub_tree_node == NULL)
    return false;

  if (node->data == sub_tree_node->data)
  {
    bool ans = is_identical(node, sub_tree_node);
    // only return true, if the answer is true, if the answer is false, check for another nodes
    if (ans == true)
      return true;
  }

  bool is_left_subtree_true = is_subtree(node->left, sub_tree_node);

  // if it isn't find the in the left subtree
  if (!is_left_subtree_true)
    return is_subtree(node->right, sub_tree_node);

  // if it is found in the left-subtree
  return true;
}

int main()
{
  vector<int> preorder = {1, 2, 4, -1, -1, 5, -1, -1, 3, -1, 6, -1, -1};
  Node *tree = build_tree(preorder);

  Node *subroot = new Node(2);
  subroot->left = new Node(4);
  subroot->right = new Node(5);

  cout << is_subtree(tree, subroot) << endl;

  return 0;
}
