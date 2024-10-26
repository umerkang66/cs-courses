#include <iostream>
#include <vector>

using namespace std;

struct Node
{
  int data;
  Node *left = NULL;
  Node *right = NULL;

  Node(int n) : data(n) {}
};

Node *build_tree(vector<int> &nodes)
{
  static int index = 0;
  if (index >= nodes.size() || nodes[index] == -1)
  {
    index++;
    return NULL;
  }

  Node *node = new Node(nodes[index++]);
  node->left = build_tree(nodes);
  node->right = build_tree(nodes);

  return node;
}

int height_of_tree(Node *node)
{
  if (node == NULL)
    return 0;

  int left_height = height_of_tree(node->left);
  int right_height = height_of_tree(node->right);

  // maximum of the left and right of tree, plus the
  return max(left_height, right_height) + 1;
}

int total_nodes(Node *node)
{
  if (node == NULL)
    return 0;

  int left_height = total_nodes(node->left);
  int right_height = total_nodes(node->right);

  // maximum of the left and right of tree, plus the
  return left_height + right_height + 1;
}

int sum_of_nodes(Node *node)
{
  if (node == NULL)
    return 0;

  int left_sum = sum_of_nodes(node->left);
  int right_sum = sum_of_nodes(node->right);

  // maximum of the left and right of tree, plus the
  return left_sum + right_sum + node->data;
}

int main()
{
  vector<int> preorder = {1, 2, 4, -1, -1, 5, -1, -1, 3, -1, 6, -1, -1};
  Node *tree = build_tree(preorder);

  cout << height_of_tree(tree) << endl;
  cout << total_nodes(tree) << endl;
  cout << sum_of_nodes(tree) << endl;

  return 0;
}
