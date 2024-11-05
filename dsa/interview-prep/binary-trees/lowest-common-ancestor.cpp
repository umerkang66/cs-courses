// https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/

#include <iostream>
#include <vector>
#include "node.hpp"
using namespace std;

bool find_path(Node *root, Node *n, vector<Node *> &path)
{
  if (root == NULL)
    return false;

  path.push_back(root);

  if (root == n)
    return true;

  bool is_left = find_path(root->left, n, path);
  bool is_right = find_path(root->right, n, path);

  if (is_left || is_right)
    return true;

  // pop the current node if it isn't in the both the left and right subtree
  path.pop_back();
  return false;
}

Node *lowest_common_ancestor(Node *root, Node *n1, Node *n2)
{
  vector<Node *> path1;
  vector<Node *> path2;

  bool is_found1 = find_path(root, n1, path1);
  bool is_found2 = find_path(root, n2, path2);

  if (!is_found1 || !is_found2)
    return NULL;

  Node *lca = NULL;

  for (int i = 0, j = 0; i < path1.size() && j < path2.size(); i++, j++)
  {
    if (path1[i] != path2[j])
      return lca;

    // both are same
    lca = path1[i];
  }

  return lca;
}

Node *lowest_common_ancestor_optimized(Node *root, Node *n1, Node *n2)
{
  if (root == NULL)
    return NULL;

  // one of them is found
  if (root == n1 || root == n2)
    return root;

  Node *left_ans = lowest_common_ancestor_optimized(root->left, n1, n2);
  Node *right_ans = lowest_common_ancestor_optimized(root->right, n1, n2);

  // if left and right are both found, current_node is the answer
  if (left_ans && right_ans)
    return root;

  // which ans exists, return it
  return left_ans == NULL ? right_ans : left_ans;
}

int main()
{
  vector<int> preorder = {1, 2, 4, -1, -1, 5, -1, -1, 3, -1, 6, -1, -1};
  Node *tree = build_tree(preorder);

  Node *four = tree->left->left;
  Node *five = tree->left->right;

  Node *answer = lowest_common_ancestor(tree, four, five);
  if (answer != NULL)
    cout << answer->data << endl; // 2

  Node *answer2 = lowest_common_ancestor_optimized(tree, four, five);
  if (answer2 != NULL)
    cout << answer2->data << endl; // 2

  return 0;
}
