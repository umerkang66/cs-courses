// https://leetcode.com/problems/delete-node-in-a-bst/

#include <iostream>
#include "node.hpp"
using namespace std;

Node *inorder(Node *root)
{
  Node *temp = root;
  while (temp->left != NULL)
    temp = temp->left;
  return temp;
}

Node *delete_in_bst(Node *root, int n)
{
  if (root == NULL)
    return NULL;

  if (n < root->data)
    root->left = delete_in_bst(root->left, n);
  else if (n > root->data)
    root->right = delete_in_bst(root->right, n);
  else
  {
    // root is found
    // CASE 1: if it is leaf node
    if (!root->left && !root->right)
    {
      delete root;
      return NULL;
    }

    // CASE 2: if it has only 1 child
    if ((root->left && !root->right) || (root->right && !root->left))
    {
      Node *next = root->left ? root->left : root->right;
      delete root;
      return next;
    }

    // CASE 3: root has both childs
    // 1: Replace value with inorder successor
    // 2: delete inorder successor
    Node *inorder_item = inorder(root->right);
    root->data = inorder_item->data;
    // this deletion will be handled by the above two cases, because inorder successor does not have 2 childs, only 0 or 1
    root->right = delete_in_bst(root->right, inorder_item->data);
    return root;
  }

  return root;
}

int main()
{
  vector<int> arr = {8, 5, 3, 6, 1, 4, 10, 11, 14};
  Node *tree = build_from_arr(arr);

  show(tree);

  delete_in_bst(tree, 8);

  show(tree);

  return 0;
}
