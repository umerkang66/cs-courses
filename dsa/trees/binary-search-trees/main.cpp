#include <iostream>
using namespace std;

struct Node
{
  Node *left = nullptr;
  Node *right = nullptr;
  int value;
  Node(int n) : value(n) {}
};

// every element should be unique
class BinarySearchTree
{
  Node *head = nullptr;

  bool search_r_helper(Node *node, int n)
  {
    if (node == nullptr)
    {
      return false;
    }

    if (n > node->value)
      return search_r_helper(node->right, n);
    else if (n < node->value)
      return search_r_helper(node->left, n);
    else
      return true;
  }

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
  BinarySearchTree() {}
  BinarySearchTree(int n)
  {
    Node *new_node = new Node(n);
    head = new_node;
  }

  BinarySearchTree &insert(int n)
  {
    Node *new_node = new Node(n);
    if (!head)
    {
      head = new_node;
      return *this;
    }

    bool is_found = search(n);
    // only add is element is not found
    if (!is_found)
    {
      Node *tail = nullptr;
      Node *current = head;

      while (current != nullptr)
      {
        if (n > current->value)
        {
          tail = current;
          current = current->right;
        }
        else if (n < current->value)
        {
          tail = current;
          current = current->left;
        }
      }

      if (n < tail->value)
      {
        tail->left = new Node(n);
        return *this;
      }

      tail->right = new Node(n);
    }

    return *this;
  }

  bool search(int n)
  {
    return search_r_helper(head, n);
  }

  ~BinarySearchTree()
  {
    delete_nodes(head);
  }
};

int main()
{
  BinarySearchTree bst(5);
  bst.insert(10).insert(4).insert(11).insert(20).insert(15).insert(100).insert(13);

  if (bst.search(15))
  {
    cout << "Found" << endl;
  }
  else
  {
    cout << "Not Found" << endl;
  }

  return 0;
}
