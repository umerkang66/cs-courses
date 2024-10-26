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

// print itself
// print left-subtree
// print right-subtree
void preorder_traversal(Node *node)
{
  if (node == NULL)
    return;

  cout << node->data << ' ';
  preorder_traversal(node->left);
  preorder_traversal(node->right);
}

// print left-subtree
// print itself
// print right-subtree
void inorder_traversal(Node *node)
{
  if (node == NULL)
    return;

  inorder_traversal(node->left);
  cout << node->data << ' ';
  inorder_traversal(node->right);
}

// print left-subtree
// print right-subtree
// print itself
void postorder_traversal(Node *node)
{
  if (node == NULL)
    return;

  postorder_traversal(node->left);
  postorder_traversal(node->right);
  cout << node->data << ' ';
}

int main()
{
  vector<int> preorder = {1, 2, 4, -1, -1, 5, -1, -1, 3, -1, 6, -1, -1};
  Node *tree = build_tree(preorder);

  cout << "preorder: ";
  preorder_traversal(tree);
  cout << endl;

  cout << "inorder: ";
  inorder_traversal(tree);
  cout << endl;

  cout << "postorder: ";
  postorder_traversal(tree);
  cout << endl;

  return 0;
}
