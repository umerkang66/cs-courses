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

int height_of_tree(Node *node, int curr_sum = 0)
{
  if (node == NULL)
    return curr_sum;

  int left_height = height_of_tree(node->left, curr_sum + 1);
  int right_height = height_of_tree(node->right, curr_sum + 1);

  return max(left_height, right_height);
}

int main()
{
  vector<int> preorder = {1, 2, 4, -1, -1, 5, -1, -1, 3, -1, 6, -1, -1};
  Node *tree = build_tree(preorder);

  cout << height_of_tree(tree) << endl;

  return 0;
}
