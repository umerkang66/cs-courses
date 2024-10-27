// https://leetcode.com/problems/diameter-of-binary-tree/
// IN THE LEETCODE, subtract the 1 from the answer they don't include the current node

#include <iostream>
#include <vector>
#include "./node.hpp"
using namespace std;

int height_of_tree(Node *node)
{
  if (node == NULL)
    return 0;

  int left_height = height_of_tree(node->left);
  int right_height = height_of_tree(node->right);

  // maximum of the left and right of tree, plus the
  return max(left_height, right_height) + 1;
}

// the longest distance between two distant nodes (n^2)
int diameter(Node *node)
{
  if (node == NULL)
    return 0;

  int curr_diameter = height_of_tree(node->left) + height_of_tree(node->right) + 1;

  int left_diameter = diameter(node->left);
  int right_diameter = diameter(node->right);

  return max(curr_diameter, max(left_diameter, right_diameter));
}

// first is diameter, second is height
pair<int, int> diameter_optimized(Node *node)
{
  if (node == NULL)
    return make_pair(0, 0);

  pair<int, int> left_data = diameter_optimized(node->left);
  pair<int, int> right_data = diameter_optimized(node->right);

  int curr_diameter = left_data.second + right_data.second + 1;

  int final_diameter = max(curr_diameter, max(left_data.first, right_data.first));

  int final_height = max(left_data.second, right_data.second) + 1;

  return make_pair(final_diameter, final_height);
}

int main()
{
  vector<int> preorder = {1, 2, 4, -1, -1, 5, -1, -1, 3, -1, 6, -1, -1};
  Node *tree = build_tree(preorder);

  cout << diameter(tree) << endl;
  pair<int, int> result = diameter_optimized(tree);
  cout << result.first << endl;

  return 0;
}
