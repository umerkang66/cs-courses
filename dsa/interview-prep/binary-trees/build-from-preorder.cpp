#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Node
{
  int data;
  Node *left = NULL;
  Node *right = NULL;

  Node(int n) : data(n) {}
};

// this will return the root
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

int main()
{
  vector<int> preorder = {1, 2, 4, -1, -1, 5, -1, -1, 3, -1, 6, -1, -1};

  Node *result = build_tree(preorder);

  return 0;
}
