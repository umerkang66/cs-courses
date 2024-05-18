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

class BinaryTree
{
  Node *root;

  void append_nodes(Node *node, Queue<int> *queue)
  {
    if (queue->is_empty())
    {
      return;
    }

    node->left = new Node(queue->dequeue());
    node->right = new Node(queue->dequeue());

    append_nodes(node->left, queue);
    append_nodes(node->right, queue);
  }

  Node *build_tree(Node *node)
  {
    cout << "Enter the data: " << endl;
    int data;
    cin >> data;
    node = new Node(data);

    if (data == -1)
    {
      return nullptr;
    }

    cout << "Enter data for inserting in left of " << data << endl;
    node->left = build_tree(node->left);
    cout << "Enter data for inserting in right of " << data << endl;
    node->right = build_tree(node->right);
    return node;
  }

  void delete_nodes_destructor(Node *node)
  {
    if (node == nullptr)
    {
      return;
    }

    delete_nodes_destructor(node->left);
    delete_nodes_destructor(node->right);

    delete node;
  }

public:
  BinaryTree(Queue<int> *queue)
  {
    root = new Node(queue->dequeue());
    append_nodes(root, queue);
  }

  BinaryTree()
  {
    root = build_tree(root);
  }

  Node *get_root()
  {
    return root;
  }

  // bfs
  void level_order_traversal(Node *root)
  {
    Queue<Node *> queue;
    queue.enqueue(root);
    queue.enqueue(nullptr);

    while (!queue.is_empty())
    {
      Node *temp = queue.dequeue();

      if (temp == nullptr)
      {
        cout << endl;
        if (!queue.is_empty())
        {
          queue.enqueue(nullptr);
        }
      }
      else
      {
        cout << temp->data << " ";
        if (temp->left)
          queue.enqueue(temp->left);
        if (temp->right)
          queue.enqueue(temp->right);
      }
    }
  }

  void dfs_preorder(Node *node)
  {
    if (!node)
    {
      return;
    }
    cout << node->data << " ";
    dfs_preorder(node->left);
    dfs_preorder(node->right);
  }

  void dfs_postorder(Node *node)
  {
    if (!node)
    {
      return;
    }
    dfs_preorder(node->left);
    dfs_preorder(node->right);
    cout << node->data << " ";
  }

  void dfs_inorder(Node *node)
  {
    if (!node)
    {
      return;
    }
    dfs_preorder(node->left);
    cout << node->data << " ";
    dfs_preorder(node->right);
  }

  ~BinaryTree()
  {
    delete_nodes_destructor(root);
  }
};

int main()
{
  // 1 3 7 -1 -1 11 -1 -1 5 17 -1 -1 -1
  BinaryTree tree;
  tree.level_order_traversal(tree.get_root());
  cout << endl;

  tree.dfs_preorder(tree.get_root());
  cout << endl;

  tree.dfs_postorder(tree.get_root());
  cout << endl;

  tree.dfs_inorder(tree.get_root());
  cout << endl;
  return 0;
}
