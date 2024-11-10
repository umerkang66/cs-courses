
#include <iostream>
#include <vector>
#include "node.hpp"
using namespace std;

struct Info
{
  bool isBST;
  int min, max, size;

  Info(bool isBST, int min, int max, int size)
      : isBST(isBST), min(min), max(max), size(size) {}
};

static int max_size = 0;

Info *largest_bst_in_bt(Node *root)
{
  if (root == NULL)
    return new Info(true, INT32_MAX, INT32_MIN, 0);

  Info *leftInfo = largest_bst_in_bt(root->left);
  Info *rightInfo = largest_bst_in_bt(root->right);

  bool isBST = leftInfo->isBST && rightInfo->isBST && root->data > leftInfo->max && root->data < rightInfo->min;

  int curr_min = min(root->data, min(leftInfo->min, rightInfo->min));
  int curr_max = max(root->data, max(leftInfo->max, rightInfo->max));
  int curr_size = leftInfo->size + rightInfo->size + 1;

  if (isBST)
  {
    max_size = max(max_size, curr_size);
    return new Info(true, curr_min, curr_max, curr_size);
  }
  else
    return new Info(false, INT32_MAX, INT32_MIN, 0);
}

int main()
{
  // this sorted array is technically, inorder sequence of bst
  Node *root = new Node(50);
  root->left = new Node(30);
  root->left->left = new Node(5);
  root->left->right = new Node(20);
  root->right = new Node(60);
  root->right->left = new Node(45);
  root->right->right = new Node(70);
  root->right->right->left = new Node(65);
  root->right->right->right = new Node(80);

  largest_bst_in_bt(root);

  cout << max_size << endl;

  return 0;
}
