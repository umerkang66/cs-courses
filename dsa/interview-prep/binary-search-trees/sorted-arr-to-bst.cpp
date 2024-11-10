// https://leetcode.com/problems/convert-sorted-array-to-binary-search-tree/

#include <iostream>
#include "node.hpp"
using namespace std;

Node *sorted_arr_to_bst(int *nums, int start, int end)
{
  if (start > end)
    return NULL;

  int mid = start + (end - start) / 2;
  Node *new_node = new Node(nums[mid]);

  new_node->left = sorted_arr_to_bst(nums, start, mid - 1);
  new_node->right = sorted_arr_to_bst(nums, mid + 1, end);

  return new_node;
}

int main()
{
  // this sorted array is technically, inorder sequence of bst
  int nums[] = {3, 4, 5, 6, 7, 8, 9};
  Node *root = sorted_arr_to_bst(nums, 0, 6);
  show(root);

  return 0;
}
