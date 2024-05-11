#include <iostream>
#include "queue.hpp"

using namespace std;

struct Node
{
  int data;
  Node *left = nullptr;
  Node *right = nullptr;

  Node(int data) : data(data) {}
};

class Tree
{
  Node *root;

  void append_nodes(Node *root, Queue<int> *queue)
  {
    if (queue->is_empty())
    {
      return;
    }

    root->left = new Node(queue->dequeue());
    root->right = new Node(queue->dequeue());

    append_nodes(root->left, queue);
    append_nodes(root->right, queue);
  }

  void build_tree(Node *root)
  {
    cout << "Enter the data: ";
    int n;
    cin >> n;
    root = new Node(n);

    if (n == -1)
    {
      return;
    }

    cout << "Enter left of " << n << ": " << endl;
    build_tree(root->left);
    cout << "Enter right of " << n << ": " << endl;
    build_tree(root->right);
  }

public:
  Tree(Queue<int> *queue)
  {
    root = new Node(queue->dequeue());
    append_nodes(root, queue);
  }

  Tree()
  {
    build_tree(root);
  }

  Node *get_root()
  {
    return root;
  }

  void delete_nodes(Node *node)
  {
    if (node == nullptr)
    {
      return;
    }

    delete_nodes(node->left);
    delete_nodes(node->right);

    delete node;
  }

  ~Tree()
  {
    delete_nodes(root);
  }
};

int main()
{
  Queue<int> queue;
  queue.enqueue(1).enqueue(2).enqueue(3).enqueue(4).enqueue(5).enqueue(6).enqueue(7);

  Tree tree(&queue);

  return 0;
}
