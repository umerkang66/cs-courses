#include <iostream>
#include <vector>
#include "node.hpp"
using namespace std;

Node *lowest_common_ancestor(Node *root, Node *n1, Node *n2)
{
  if (root == NULL)
    return NULL;

  // one of them is found
  if (root == n1 || root == n2)
    return root;

  Node *left_ans = lowest_common_ancestor(root->left, n1, n2);
  Node *right_ans = lowest_common_ancestor(root->right, n1, n2);

  // if left and right are both found, current_node is the answer
  if (left_ans && right_ans)
    return root;

  // which ans exists, return it
  return left_ans == NULL ? right_ans : left_ans;
}

int find_distance(Node *root, Node *n)
{
  if (root == NULL)
    return -1;

  if (root == n)
    return 0;

  int left = find_distance(root->left, n);
  int right = find_distance(root->right, n);

  if (left == -1 && right == -1)
    return -1;

  return left == -1 ? right + 1 : left + 1;
}

int min_distance_between_nodes(Node *root, Node *n1, Node *n2)
{
  Node *lca = lowest_common_ancestor(root, n1, n2);

  int lca_to_n1 = find_distance(lca, n1);
  int lca_to_n2 = find_distance(lca, n2);

  return lca_to_n1 + lca_to_n2;
}

int main()
{
  vector<int> preorder = {1, 2, 4, -1, -1, 5, -1, -1, 3, -1, 6, -1, -1};
  Node *tree = build_tree(preorder);

  Node *four = tree->left->left;
  Node *five = tree->left->right;

  cout << min_distance_between_nodes(tree, four, five) << endl;

  Node *six = tree->right->right;

  cout << min_distance_between_nodes(tree, four, six) << endl;

  return 0;
}
