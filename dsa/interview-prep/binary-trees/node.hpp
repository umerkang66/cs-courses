#include <iostream>
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