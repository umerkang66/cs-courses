// https://leetcode.com/problems/maximum-sum-bst-in-binary-tree/

#include <iostream>
#include <vector>
#include "node.hpp"
using namespace std;

struct Info
{
  bool isBST;
  int min, max, sum;

  Info(bool isBST, int min, int max, int sum)
      : isBST(isBST), min(min), max(max), sum(sum) {}
};

static int max_sum = 0;

Info *largest_bst_in_bt(Node *root)
{
  if (root == NULL)
    return new Info(true, INT32_MAX, INT32_MIN, 0);

  Info *leftInfo = largest_bst_in_bt(root->left);
  Info *rightInfo = largest_bst_in_bt(root->right);

  bool isBST = leftInfo->isBST && rightInfo->isBST && root->data > leftInfo->max && root->data < rightInfo->min;

  int curr_min = min(root->data, min(leftInfo->min, rightInfo->min));
  int curr_max = max(root->data, max(leftInfo->max, rightInfo->max));
  int curr_sum = leftInfo->sum + rightInfo->sum + root->data;

  if (isBST)
  {
    max_sum = max(max_sum, curr_sum);
    return new Info(true, curr_min, curr_max, curr_sum);
  }

  // currnode is not bst
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

  cout << max_sum << endl;

  return 0;
}
