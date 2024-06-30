#include <iostream>
#include <vector>

using namespace std;

struct Node
{
  Node *left = nullptr;
  Node *right = nullptr;
  int value;
  Node(int n) : value(n) {}
};

class AVL
{
public:
  Node *head = nullptr;

  void delete_nodes(Node *node)
  {
    if (node == nullptr)
      return;

    if (node->left)
      delete_nodes(node->left);
    if (node->right)
      delete_nodes(node->right);

    delete node;
  }

public:
  AVL() {}
  AVL(vector<int> &nums)
  {
    for (int num : nums)
    {
      insert(num);
    }
  }
  AVL(int n)
  {
    Node *new_node = new Node(n);
    head = new_node;
  }
  ~AVL() { delete_nodes(head); }

  AVL &insert(int n)
  {
    Node *new_node = new Node(n);
    if (!head)
    {
      head = new_node;
      return *this;
    }

    Node *tail = nullptr;
    Node *current = head;

    while (current != nullptr)
    {
      tail = current;
      if (n > current->value)
      {
        current = current->right;
      }
      else if (n < current->value)
      {
        current = current->left;
      }
    }

    if (n < tail->value)
    {
      tail->left = new Node(n);
      return *this;
    }

    tail->right = new Node(n);
    return *this;
  }
};

int main()
{
  AVL avl;
  avl.insert(1).insert(2).insert(3);

  return 0;
}
